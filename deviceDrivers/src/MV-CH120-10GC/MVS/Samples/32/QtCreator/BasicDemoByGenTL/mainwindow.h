#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MvCamera.h"

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
    void EnableControls(bool bIsCameraReady);//�жϰ�ťʹ��
    int SetTriggerMode();                // ch:���ô���ģʽ | en:Set Trigger Mode
    int GetTriggerMode();

private slots:
    void on_EnumInterface_clicked();

    void on_EnumDevice_clicked();

    void on_OpenDevice_clicked();

    void on_CloseDevice_clicked();

    void on_StartGrab_clicked();

    void on_StopGrab_clicked();

    void on_SoftCheckBox_clicked();

    void on_SoftOnceButton_clicked();

    void on_ContinueRadioButton_clicked();

    void on_TriggerRadioButton_clicked();

private:
    Ui::MainWindow *ui;
    MV_GENTL_IF_INFO_LIST   m_stIFList;
    MV_GENTL_DEV_INFO_LIST  m_stDevList;
    void*                   m_hWnd;
    bool                    m_bOpenDevice;                        // ch:�Ƿ���豸 | en:Whether to open device
    bool                    m_bStartGrabbing;                     // ch:�Ƿ�ʼץͼ | en:Whether to start grabbing
    bool                    m_bSoftWareTriggerCheck;			// ch:�Ƿ����� | en:Whether to software
    bool                    m_bContinueRadioButton;				// ch:����ģʽ��ť | en:continue button
    bool                    m_bTriggerRadioButton;				//ch:����ģʽ��ť | en:Trigger button


    CMvCamera*     m_pcMyCamera;
    int                     m_nTriggerMode;                       // ch:����ģʽ | en:Trigger Mode
    int                     m_nTriggerSource;                     // ch:����Դ | en:Trigger Source

};

#endif // MAINWINDOW_H
