#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MvCamera.h"
#include <map>
#include <QMap>
#include <QDebug>

#define MV_TRIGGER_SOURCE_EncoderModuleOut 6

#define STR_SOFTWARE "Software"
#define STR_FRAMEBURSTSTART "FrameBurstStart"

//模拟增益
typedef enum _MV_PREAMP_GAIN_
{
    GAIN_1000x = 1000,
    GAIN_1400x = 1400,
    GAIN_1600x = 1600,
    GAIN_2000x = 2000,
    GAIN_2400x = 2400,
    GAIN_4000x = 4000,
    GAIN_3200x = 3200,

}MV_PREAMP_GAIN;

//ImageCompressionMode模式
typedef enum _MV_IMAGE_COMPRESSION_MODE_
{
    IMAGE_COMPRESSION_MODE_OFF = 0,
    IMAGE_COMPRESSION_MODE_HB = 2,
}MV_IMAGE_COMPRESSION_MODE;

//触发选项
typedef enum _MV_CAM_TRIGGER_OPTION_
{
    FRAMEBURSTSTART = 6,
    LINESTART = 9,
}MV_CAM_TRIGGER_OPTION;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void static __stdcall ImageCallBack(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
    void ImageCallBackInner(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInf);

private:
    void ShowErrorMsg(QString csMessage, unsigned int nErrorNum);

    void EnableControls(bool bIsCameraReady);

    int GetImageCompressionMode();
    int GetTriggerSelector();
    int GetTriggerSwitch();
    int GetTriggerMode();
    int GetExposureTime();                                      // ch:获取曝光时间 | en:Get Exposure Time
    int SetExposureTime();                                      // ch:设置曝光时间 | en:Set Exposure Time
    int GetDigitalShiftGain();                                  // ch:获取数字增益 | en:Get Gain
    int SetDigitalShiftGain();                                  // ch:设置数字增益 | en:Set Gain
    int GetPreampGain();                                        // ch:获取模拟增益 | en:Get PreampGain
    int GetTriggerSource();                                     // ch:获取触发源 | en:Get Trigger Source
    int GetPixelFormat();                                       // ch:获取像素格式 | en:Get Pixel Format
    int GetAcquisitionLineRate();                               // ch:获取实际行频值 | en:Get Acquisition LineRate
    int SetAcquisitionLineRate();                               // ch:设置行频   | en:set Acquisition LineRate
    int GetAcquisitionLineRateEnable();                         // ch:获取行频使能开关 | en:Get Acquisition LineRate Enable
    int GetResultingLineRate();                                 // ch:获取实际行频 | en:Get Resulting LineRate

    int SaveImage(MV_SAVE_IAMGE_TYPE enSaveImageType);          // ch:保存图片 | en:Save Image




private slots:
    void on_EnumButton_clicked();

    void on_OpenButton_clicked();

    void on_GetParameterButton_clicked();

    void on_StartGrabbingButton_clicked();

    void on_CloseButton_clicked();

    void on_StopGrabbingButton_clicked();

    void on_SetParameterButton_clicked();

    void on_SelchangeTriggerselCombo_currentTextChanged(const QString &arg1);

    void on_SelchangeTriggerswitchCombo_currentTextChanged(const QString &arg1);

    void on_SelchangeTriggersourceCombo_currentTextChanged(const QString &arg1);

    void on_SoftwareOnceButton_clicked();


    void on_SelchangePixelformatCombo_currentTextChanged(const QString &arg1);

    void on_SelchangeImageCompressionModeCombo_currentTextChanged(const QString &arg1);

    void on_ExposureTimeLineEdit_editingFinished();

    void on_SelchangePreampgainCombo_currentTextChanged(const QString &arg1);

    void on_PreampGainLineEdit_editingFinished();

    void on_AcquisitionLineRateLineEdit_editingFinished();

    void on_AcquisitionLineRateEnableCheckBox_clicked(bool checked);

    void on_SaveBmpButton_clicked();

    void on_SaveJpgButton_clicked();

    void on_SaveTiffButton_clicked();

    void on_SavePngButton_clicked();

private:
    Ui::MainWindow *ui;

    void *m_hWnd;     //disPlay handle

    MV_CC_DEVICE_INFO_LIST  m_stDevList;

    CMvCamera*              m_pcMyCamera;

    bool                    m_bGrabbing;      // 是否开始抓图
    bool                    m_bOpenDevice;    // ch:是否打开设备 | en:Whether to open device
    int                     m_nTriggerMode;                     // ch:触发模式 | en:Trigger Mode
    int                     m_nTriggerSelector;
    int                     m_nTriggerSource;
    int                     m_nPreampGain;
    int                     m_nPixelFormat;
    int                     m_nImageCompressionMode;
    float                   m_dExposureEdit;
    float                   m_dDigitalShiftGainEdit;
    int                     m_nAcquisitionLineRateEdit;
    unsigned int            m_nSaveImageBufSize;

    bool                    m_bTriggerModeCheck;
    bool                    m_bPreampGain;
    bool                    m_bAcquisitionLineRate;
    bool                    m_bHBMode;
    unsigned char*          m_pSaveImageBuf;
    MV_FRAME_OUT_INFO_EX    m_stImageInfo;

    pthread_mutex_t        m_hSaveImageMux;
    int CloseDevice();                                          // ch:关闭设备 | en:Close Device


    QMap<QString, int> m_mapPixelFormat;
    QMap<QString, int> m_mapPreampGain;
    QMap<QString, int> m_mapTriggerSource;

};

#endif // MAINWINDOW_H
