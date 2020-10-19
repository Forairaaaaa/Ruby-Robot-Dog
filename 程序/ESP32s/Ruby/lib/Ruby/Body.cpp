/*
 * Body.cpp
 * ������Ƴ���
 * ����: 2020.10.6
 * ����: Forairaaaaa
 */

#include "Legs.h"


// ���������ȶ��󣬶���ؽ���λ����
Legs LF(1,2,3,535,518,480);
Legs RF(4,5,6,500,484,536);
Legs LB(7,8,9,522,544,491);
Legs RB(10,11,12,539,488,525);


// �����������ֵ
float Xexp = 0;
float Yexp = 0;
float Zexp = 0;


// ��̬���ݼ�       step:����   step_h:����   body_h:λ��
float TROT_Set[4][3] = {
    {0,3,-12},              // LF
    {0,3,-12},              // RF
    {0,3,-12},              // LB
    {0,3,-12}               // RB
};


/***************************************��ʼ��***************************************/
// �����Ȼع�ԭ��
void Body_Gohome(int x, int y)
{
    LF.Go_Coordinate(x,y);
    RF.Go_Coordinate(x,y);
    LB.Go_Coordinate(x,y);
    RB.Go_Coordinate(x,y);
    LF.Go_Action();
}


// Ruby��ʼ�����������ڣ���������˶������괦
void Body_init(int x, int y)
{
    Drive_Serial_Init();
    Body_Gohome(x, y);
    Serial.println("Ruby's initialization complete!");
}






/***************************************8���ɶȲ�̬**************************************/
// ��СJerk�켣�滮
// t:ʱ����   Xs:X���   Xf:X�յ�   Zs:Z���   H:̧�ȸ߶�   Ts:��̬����   D_Sup:֧����ռ�ձ�  (Ys,Yfͬ��)
void Jerk_Trail(float t, float Xs, float Xf, float Ys, float Yf, float Zs, float H, float Ts, float D_Sup)
{
    float sigma = (2*M_PI*t)/(D_Sup*Ts);
    Xexp  = (Xf-Xs)*((sigma-sin(sigma))/(2*M_PI))+Xs;
    Yexp  = (Yf-Ys)*((sigma-sin(sigma))/(2*M_PI))+Ys;
    Zexp  = H*((1-cos(sigma))/2)+Zs;
}


// �򵥶Խǲ�̬
// t:ʱ����   step:����   step_h:����   body_h:λ��   Ts:��̬����
void Gait_TROT(float t, float step, float step_h, float body_h, float Ts)
{

    if(t<0 || t>Ts){
        Serial.println("Wrong t");
        Body_Gohome(0,0);
        return;
    }

    // �켣��任
    float Xs = step/2;
    float Xf = -Xs;
    float Zs = body_h;
    float H  = step_h;


    // ǰ������
    if(t<=(Ts*0.5)){
        // ˢ�°������������
        Jerk_Trail(t, Xs, Xf, 0, 0, Zs, H, Ts, 0.5);
        LF.Go_Coordinate(Xexp,Zexp);
        RB.Go_Coordinate(Xexp,Zexp);
        // ˢ��֧�����������
        Jerk_Trail(t, Xf, Xs, 0, 0, Zs, 0, Ts, 0.5);
        RF.Go_Coordinate(Xexp,Zexp);
        LB.Go_Coordinate(Xexp,Zexp);
        // �˶�ִ��
        LF.Go_Action();
    }else{
        t=t-(Ts*0.5);
        // ˢ�°������������
        Jerk_Trail(t, Xs, Xf, 0, 0, Zs, H, Ts, 0.5);
        RF.Go_Coordinate(Xexp,Zexp);
        LB.Go_Coordinate(Xexp,Zexp);
        // ˢ��֧�����������
        Jerk_Trail(t, Xf, Xs, 0, 0, Zs, 0, Ts, 0.5);
        LF.Go_Coordinate(Xexp,Zexp);
        RB.Go_Coordinate(Xexp,Zexp);
        // �˶�ִ��
        LF.Go_Action();
    }
}


// ���ȶԽǲ�̬�� Gait_Action()��Ч
// t:ʱ����   step:����   step_h:����   body_h:λ��   Ts:��̬����   leg: 1(LF)��2(RF)��3(LB)��4(RB)  
void Gait_TROT_Senior(float t, float step, float step_h, float body_h, float Ts, u8 leg)
{
    if(leg > 4)                         // ����ж�
        leg = 1;
    if(t<0 || t>Ts){
        Serial.println("Wrong t");
        Body_Gohome(0,0);
        return;
    }

    // �켣��任
    float Xs = step/2;
    float Xf = -Xs;
    float H  = step_h;
    float Zs = -body_h;

    // ǰ������
    if(t<=(Ts*0.5)){
        switch (leg){     
            case 1:
                Jerk_Trail(t, Xs, Xf, 0, 0, Zs, H, Ts, 0.5);              // ˢ�°������������
                LF.Go_Coordinate(Xexp,Zexp);                              // 1
                break;
            case 4:
                Jerk_Trail(t, Xs, Xf, 0, 0, Zs, H, Ts, 0.5);
                RB.Go_Coordinate(Xexp,Zexp);                              // 4
                break;
            case 2:
                Jerk_Trail(t, Xf, Xs, 0, 0, Zs, 0, Ts, 0.5);              // ˢ��֧�����������
                RF.Go_Coordinate(Xexp,Zexp);                              // 2
                break;
            case 3:
                Jerk_Trail(t, Xf, Xs, 0, 0, Zs, 0, Ts, 0.5);
                LB.Go_Coordinate(Xexp,Zexp);                              // 3
                break;
        }

    // �������
    }else{
        t=t-(Ts*0.5);
        switch (leg){     
            case 1:
                Jerk_Trail(t, Xf, Xs, 0, 0, Zs, 0, Ts, 0.5);              // ˢ��֧�����������
                LF.Go_Coordinate(Xexp,Zexp);                              // 1
                break;
            case 4:
                Jerk_Trail(t, Xf, Xs, 0, 0, Zs, 0, Ts, 0.5);
                RB.Go_Coordinate(Xexp,Zexp);                              // 4
                break;
            case 2:
                Jerk_Trail(t, Xs, Xf, 0, 0, Zs, H, Ts, 0.5);              // ˢ�°������������
                RF.Go_Coordinate(Xexp,Zexp);                              // 2
                break;
            case 3:
                Jerk_Trail(t, Xs, Xf, 0, 0, Zs, H, Ts, 0.5);
                LB.Go_Coordinate(Xexp,Zexp);                              // 3
                break;
        }
    }
}


// ��ִ̬��
void Gait_Action(){
    LF.Go_Action();
}

// �ɲ�̬�����ɲ�̬
void Gait_TROT_FromSet(float t, float Ts)
{
    Gait_TROT_Senior(t, TROT_Set[0][0], TROT_Set[0][1], TROT_Set[0][2], Ts, 1);
    Gait_TROT_Senior(t, TROT_Set[1][0], TROT_Set[1][1], TROT_Set[1][2], Ts, 2);
    Gait_TROT_Senior(t, TROT_Set[2][0], TROT_Set[2][1], TROT_Set[2][2], Ts, 3);
    Gait_TROT_Senior(t, TROT_Set[3][0], TROT_Set[3][1], TROT_Set[3][2], Ts, 4);
    LF.Go_Action();
}

// �޸����ݼ�   step:����   step_h:����   body_h:λ��   leg: 1(LF)��2(RF)��3(LB)��4(RB)
void TROT_DataSet(u8 leg, float step, float step_h, float body_h)
{
    switch (leg)
    {
    case 1:
        TROT_Set[0][0] = step;  TROT_Set[0][1] = step_h;  TROT_Set[0][2] = body_h;
        break;
    case 2:
        TROT_Set[1][0] = step;  TROT_Set[1][1] = step_h;  TROT_Set[1][2] = body_h;
        break;
    case 3:
        TROT_Set[2][0] = step;  TROT_Set[2][1] = step_h;  TROT_Set[2][2] = body_h;
        break;
    case 4:
        TROT_Set[3][0] = step;  TROT_Set[3][1] = step_h;  TROT_Set[3][2] = body_h;
        break;
    default:
        break;
    }
}


// 8���ɶ�Ӧ�ò㺯����ˮ����
/*

    _____
  1|     |2       V_y
   |     |      ^
   |     |      |
  3|_____|4     | 
                 ������������> V_x

// Pitch��������    Roll��������
 
   ȡֵ��Χ����Ӧ��
                         0   1   2   3   4   5   6   7   8   9
                        -5  -4  -3  -2  -1   0   1   2   3   4


// step_max����������ֵ    step_h������

*/


void DOF8_TROT(float step_l, float step_r, float Pitch, float Roll, float speed, float step_max, float step_h)
{

    float i = 0;                           // t
    float htimes = 2;                      // �߶Ȳ��

    
    if((step_l==0) && (step_r==0))         // ԭ��վ��ʱ����Ϊ0
        step_h = 0;


    // ˮƽ�ƶ��任
    step_l *= (step_max/4);
    step_r *= (step_max/4);
    
    
    // ��̬  ���̵�һ��

    if((Pitch==0) && (Roll==0)){           // �����ı�λ��
        for(i=0;i<=1;i+=speed){
            TROT_DataSet(1,step_l,step_h,-14);
            TROT_DataSet(2,step_r,step_h,-14);
            TROT_DataSet(3,step_l,step_h,-14);
            TROT_DataSet(4,step_r,step_h,-14);
            Gait_TROT_FromSet(i, 1);
        }
    }
    else if(Pitch!=0){                     // ���ı丩����
        for(i=0;i<=1;i+=speed){
            TROT_DataSet(1,step_l,step_h,Pitch*htimes);
            TROT_DataSet(2,step_r,step_h,Pitch*htimes);
            TROT_DataSet(3,step_l,step_h,-(Pitch*htimes));
            TROT_DataSet(4,step_r,step_h,-(Pitch*htimes));
            Gait_TROT_FromSet(i, 1);
        }
    }
    else{                                  // ���ı������
        for(i=0;i<=1;i+=speed){
            TROT_DataSet(1,step_l,step_h,Roll*htimes);
            TROT_DataSet(2,step_r,step_h,-(Roll*htimes));
            TROT_DataSet(3,step_l,step_h,Roll*htimes);
            TROT_DataSet(4,step_r,step_h,-(Roll*htimes));
            Gait_TROT_FromSet(i, 1);
        }
    }


}






/**************************************���Ժ���***************************************/
// ������
void In_kine()
{
    int x = 0;
    int y = 0;

    Serial.println(LF.In_kinematic(x,y,2));
    Serial.println("  ");
    Serial.println(LF.In_kinematic(x,y,1));
    Serial.println("-------------");

    x = -20;
    y = 0;
    Serial.println(LF.In_kinematic(x,y,2));
    Serial.println("  ");
    Serial.println(LF.In_kinematic(x,y,1));
    Serial.println("-------------");

    x = 5;
    y = -10;
    Serial.println(LF.In_kinematic(x,y,2));
    Serial.println("  ");
    Serial.println(LF.In_kinematic(x,y,1));
    int shit = LF.In_kinematic(x,y,1);
    Serial.println(shit);
    Serial.println("=============");
}

// ������⶯������
void In_kine_Test()
{
    float i = 0,j = 0;

    for(j=0;j<2;j++){
        for(i=10;i>-30;i-=1){
        LF.Go_Coordinate(0,i);
        RF.Go_Coordinate(0,i);
        LB.Go_Coordinate(0,i);
        RB.Go_Coordinate(0,i);
        LF.Go_Action();
        delay(10);
        }
        for(i=-30;i<10;i+=1){
            LF.Go_Coordinate(0,i);
            RF.Go_Coordinate(0,i);
            LB.Go_Coordinate(0,i);
            RB.Go_Coordinate(0,i);
            LF.Go_Action();
            delay(10);
        }
    }
    LF.Go_Coordinate(0,-10,0,500);
    RF.Go_Coordinate(0,-10,0,500);
    LB.Go_Coordinate(0,-10,0,500);
    RB.Go_Coordinate(0,-10,0,500);
    LF.Go_Action();
    delay(800);
    LF.Go_Coordinate(0,5,0,500);
    RF.Go_Coordinate(0,5,0,500);
    LB.Go_Coordinate(0,-25,0,500);
    RB.Go_Coordinate(0,-25,0,500);
    LF.Go_Action();
    delay(800);
    LF.Go_Coordinate(0,-25,0,500);
    RF.Go_Coordinate(0,-25,0,500);
    LB.Go_Coordinate(0,5,0,500);
    RB.Go_Coordinate(0,5,0,500);
    LF.Go_Action();
    delay(800);
    LF.Go_Coordinate(0,10,0,500);
    RF.Go_Coordinate(0,10,0,500);
    LB.Go_Coordinate(0,10,0,500);
    RB.Go_Coordinate(0,10,0,500);
    LF.Go_Action();
    delay(800);
}

// �Ȳ��ؽڷ�������
void GetPosition()
{
    LF.Print_Pos("LF");
    LF.Print_Load("LF");
    RF.Print_Pos("RF");
    RF.Print_Load("RF");
    LB.Print_Pos("LB");
    LB.Print_Load("LB");
    RB.Print_Pos("RB");
    RB.Print_Load("RB");
}


// �򵥲�̬����
void TROT_test()
{
    float i = 0;
    int j = 0;

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            Gait_TROT(i, 0, 3, 0, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            Gait_TROT(i, 0, 3, 12, 1);
        }
    }

    for(j=0;j<6;j++){
        for(i=0;i<=1;i+=0.01){
            Gait_TROT(i, 10, 3, 12, 1);
        }
    }

    for(j=0;j<6;j++){
        for(i=0;i<=1;i+=0.01){
            Gait_TROT(i, -10, 3, 12, 1);
        }
    }
}



// ���ݼ���̬����
void TROT_S_test()
{
    float i = 0;
    int j = 0;

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,0,3,-12);
            TROT_DataSet(2,0,3,-12);
            TROT_DataSet(3,0,3,0);
            TROT_DataSet(4,0,3,0);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,0,3,0);
            TROT_DataSet(2,0,3,0);
            TROT_DataSet(3,0,3,-12);
            TROT_DataSet(4,0,3,-12);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,0,3,-12);
            TROT_DataSet(2,0,3,0);
            TROT_DataSet(3,0,3,-12);
            TROT_DataSet(4,0,3,0);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,0,3,0);
            TROT_DataSet(2,0,3,-12);
            TROT_DataSet(3,0,3,0);
            TROT_DataSet(4,0,3,-12);
            Gait_TROT_FromSet(i, 1);
        }
    }

    TROT_DataSet(1,0,0,0);
    TROT_DataSet(2,0,0,0);
    TROT_DataSet(3,0,0,0);
    TROT_DataSet(4,0,0,0);
    Gait_TROT_FromSet(i, 1);

    delay(700);

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,20,3,0);
            TROT_DataSet(2,20,3,0);
            TROT_DataSet(3,20,3,0);
            TROT_DataSet(4,20,3,0);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,-20,3,12);
            TROT_DataSet(2,-20,3,12);
            TROT_DataSet(3,-20,3,12);
            TROT_DataSet(4,-20,3,12);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,-15,3,12);
            TROT_DataSet(2,15,3,12);
            TROT_DataSet(3,-15,3,12);
            TROT_DataSet(4,15,3,12);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,10,3,12);
            TROT_DataSet(2,-10,3,12);
            TROT_DataSet(3,10,3,12);
            TROT_DataSet(4,-10,3,12);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,20,3,12);
            TROT_DataSet(2,10,3,12);
            TROT_DataSet(3,20,3,12);
            TROT_DataSet(4,10,3,12);
            Gait_TROT_FromSet(i, 1);
        }   
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,-10,3,12);
            TROT_DataSet(2,-20,3,12);
            TROT_DataSet(3,-10,3,12);
            TROT_DataSet(4,-20,3,12);
            Gait_TROT_FromSet(i, 1);
        }
    }
}


void run_test()
{
    float i = 0;
    int j = 0;

    for(j=0;j<20;j++){
        for(i=0;i<=1;i+=0.02){
            TROT_DataSet(1,25,4,-14);
            TROT_DataSet(2,25,4,-14);
            TROT_DataSet(3,25,4,-14);
            TROT_DataSet(4,25,4,-14);
            Gait_TROT_FromSet(i, 1);
        }
    }

    for(j=0;j<8;j++){
        for(i=0;i<=1;i+=0.01){
            TROT_DataSet(1,0,4,-5);
            TROT_DataSet(2,0,4,-5);
            TROT_DataSet(3,0,4,-5);
            TROT_DataSet(4,0,4,-5);
            Gait_TROT_FromSet(i, 1);
        }
    }

    // for(j=0;j<12;j++){
    //     for(i=0;i<=1;i+=0.01){
    //         TROT_DataSet(1,30,6,-10);
    //         TROT_DataSet(2,30,6,-10);
    //         TROT_DataSet(3,30,6,-10);
    //         TROT_DataSet(4,30,8,-10);
    //         Gait_TROT_FromSet(i, 1);
    //     }
    // }

    // for(j=0;j<8;j++){
    //     for(i=0;i<=1;i+=0.02){
    //         TROT_DataSet(1,0,7,-5);
    //         TROT_DataSet(2,0,7,-5);
    //         TROT_DataSet(3,0,7,-5);
    //         TROT_DataSet(4,0,7,-5);
    //         Gait_TROT_FromSet(i, 1);
    //     }
    // }

    // for(j=0;j<12;j++){
    //     for(i=0;i<=1;i+=0.01){
    //         TROT_DataSet(1,20,6,-14);
    //         TROT_DataSet(2,20,6,-14);
    //         TROT_DataSet(3,20,6,-14);
    //         TROT_DataSet(4,20,6,-14);
    //         Gait_TROT_FromSet(i, 1);
    //     }
    // }

    // for(j=0;j<8;j++){
    //     for(i=0;i<=1;i+=0.02){
    //         TROT_DataSet(1,-25,4,-14);
    //         TROT_DataSet(2,-25,4,-14);
    //         TROT_DataSet(3,-25,4,-14);
    //         TROT_DataSet(4,-25,4,-14);
    //         Gait_TROT_FromSet(i, 1);
    //     }
    // }

    // for(j=0;j<16;j++){
    //     for(i=0;i<=1;i+=0.02){
    //         TROT_DataSet(1,7,6,-14);
    //         TROT_DataSet(2,25,6,-14);
    //         TROT_DataSet(3,7,6,-14);
    //         TROT_DataSet(4,25,6,-14);
    //         Gait_TROT_FromSet(i, 1);
    //     }
    // }

    // for(j=0;j<8;j++){
    //     for(i=0;i<=1;i+=0.02){
    //         TROT_DataSet(1,-10,6,-14);
    //         TROT_DataSet(2,10,6,-14);
    //         TROT_DataSet(3,-10,6,-14);
    //         TROT_DataSet(4,10,6,-14);
    //         Gait_TROT_FromSet(i, 1);
    //     }
    // }

    
}