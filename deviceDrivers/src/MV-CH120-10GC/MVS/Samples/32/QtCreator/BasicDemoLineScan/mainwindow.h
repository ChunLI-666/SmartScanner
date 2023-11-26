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

//ģ������
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

//ImageCompressionModeģʽ
typedef enum _MV_IMAGE_COMPRESSION_MODE_
{
    IMAGE_COMPRESSION_MODE_OFF = 0,
    IMAGE_COMPRESSION_MODE_HB = 2,
}MV_IMAGE_COMPRESSION_MODE;

//����ѡ��
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
    int GetExposureTime();                                      // ch:��ȡ�ع�ʱ�� | en:Get Exposure Time
    int SetExposureTime();                                      // ch:�����ع�ʱ�� | en:Set Exposure Time
    int GetDigitalShiftGain();                                  // ch:��ȡ�������� | en:Get Gain
    int SetDigitalShiftGain();                                  // ch:������������ | en:Set Gain
    int GetPreampGain();                                        // ch:��ȡģ������ | en:Get PreampGain
    int GetTriggerSource();                                     // ch:��ȡ����Դ | en:Get Trigger Source
    int GetPixelFormat();                                       // ch:��ȡ���ظ�ʽ | en:Get Pixel Format
    int GetAcquisitionLineRate();                               // ch:��ȡʵ����Ƶֵ | en:Get Acquisition LineRate
    int SetAcquisitionLineRate();                               // ch:������Ƶ   | en:set Acquisition LineRate
    int GetAcquisitionLineRateEnable();                         // ch:��ȡ��Ƶʹ�ܿ��� | en:Get Acquisition LineRate Enable
    int GetResultingLineRate();                                 // ch:��ȡʵ����Ƶ | en:Get Resulting LineRate

    int SaveImage(MV_SAVE_IAMGE_TYPE enSaveImageType);          // ch:����ͼƬ | en:Save Image




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

    bool                    m_bGrabbing;      // �Ƿ�ʼץͼ
    bool                    m_bOpenDevice;    // ch:�Ƿ���豸 | en:Whether to open device
    int                     m_nTriggerMode;                     // ch:����ģʽ | en:Trigger Mode
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
    int CloseDevice();                                          // ch:�ر��豸 | en:Close Device


    QMap<QString, int> m_mapPixelFormat;
    QMap<QString, int> m_mapPreampGain;
    QMap<QString, int> m_mapTriggerSource;

};

#endif // MAINWINDOW_H
