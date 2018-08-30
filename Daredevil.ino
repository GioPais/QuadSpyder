//<>  
#include <Servo.h>
#include <NewPing.h>

Servo hombro1;
Servo hombro2;
Servo hombro11;//3
Servo hombro12;//4

Servo muslo1;
Servo muslo2;
Servo muslo11;
Servo muslo12;

Servo pierna1;
Servo pierna2;
Servo pierna11;
Servo pierna12;

Servo leg1[] = {hombro1,muslo1,pierna1};
Servo leg2[] = {hombro2,muslo2,pierna2};
Servo leg3[] = {hombro11,muslo11,pierna11};
Servo leg4[] = {hombro12,muslo12,pierna12};


//!!!
const int pin_trig =50; // Pin para emision de pulso ultrasonico
const int pin_echo =51; // Pin para capturar eco producido absolutamente no copie esto jej
const int d_max =1000;  //definir distancia minima [cm]
int distancia;          //variable de distancia medida
NewPing sonar(pin_trig, pin_echo, d_max);
//!!!


//posiciones iniciales para cada servo
//Hombros
int pos_h1_A  = 90;
int pos_h2_A  = 90;//al revez :c
int pos_h11_A = 90;
int pos_h12_A = 90;
//Muslos
int pos_M1_A  = 140;//140
int pos_M2_A  = 100;
int pos_M11_A = 100;
int pos_M12_A = 100;
//Pie
int pos_P1_A  = 15;
int pos_P2_A  = 15;
int pos_P11_A = 165;//al revez
int pos_P12_A = 15;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
 Serial.begin (9600) ;// iniciar comunicacion serial
  hombro1.attach(4);//1
  hombro2.attach(7);//2
  hombro11.attach(10);//3
  hombro12.attach(13);//4

  muslo1.attach(3);//1
  muslo2.attach(6);//2
  muslo11.attach(9);//3
  muslo12.attach(12);//4

  pierna1.attach(2);//1
  pierna2.attach(5);//2
  pierna11.attach(8);//3
  pierna12.attach(11);//4

  hombro1.write(pos_h1_A);
  hombro2.write(pos_h2_A);
  hombro11.write(pos_h11_A);//3
  hombro12.write(pos_h12_A);//4

  muslo1.write(pos_M1_A);
  muslo2.write(pos_M2_A);
  muslo11.write(pos_M11_A);//3
  muslo12.write(pos_M12_A);//4

  pierna1.write(pos_P1_A);
  pierna2.write(pos_P2_A);
  pierna11.write(pos_P11_A);//4
  pierna12.write(pos_P12_A); //3           servo al revez uwu
  delay(1000);
}

int Posicion_robot(){
  int distancia= sonar.ping_cm();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//funcion para mover un servo una cantidad de grados

void Mov_servo(Servo motor,int grados){
  int pos_ini=motor.read();
  int pos_fin=pos_ini+grados;
  if(pos_ini<pos_fin){
    for(int pos= pos_ini; pos<=pos_fin; pos +=1){
      motor.write(pos);
      delay(15);
    }
  }
  else if(pos_ini > pos_fin){
    for(int pos= pos_ini; pos>=pos_fin; pos -=1){
      motor.write(pos);
      delay(10);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mover el "hombro" de cierta pata una cantidad de grados
void Mov_leg_hombro(Servo leg[],int grados){
  Servo motor=leg[0];
  if(leg != leg4){
   Mov_servo(motor,grados);
  }
  // movimiento pierna al revez
  else{
  Mov_servo(motor,-grados);
  delay(100);
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mover el "muslo" de cierta pata una cantidad de grados
void Mov_leg_muslo(Servo leg[],int grados){
  Servo motor=leg[1];
  Mov_servo(motor,grados);
  delay(100);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mover el "pie" de una pata una cantidad de grados
void Mov_leg_pie(Servo leg[],int grados){
  Servo motor=leg[2];
  if(leg ==leg4){
    Mov_servo(motor,-grados);
  }
  // movimiento pie al revez
  else{  
    Mov_servo(motor,grados);
    delay(100);
  }
}

  /////////////////////////////////////////////////////////////////////////////////
//Mover una pierna completa una cantidad de grados, sin arrastrarla  
void Mov_leg(Servo leg[], int grados){
  if (grados!=0){
  Mov_leg_muslo(leg,30);
  delay(100);
  Mov_leg_hombro(leg,grados);
  delay(100);
  Mov_leg_muslo(leg,-30);
  delay(100);

}
}
// funcion adelantamiento cuerpo robot (mov sensual)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mover dos piernas
void Mov_2_leg(Servo leg_i[], int grados_i,Servo leg_ii[],int grados_ii){
  Mov_sensual(leg_i,grados_i,grados_i/2);
  Mov_leg(leg_i,grados_i);
  Mov_sensual(leg_i,-grados_i,-grados_i/2);
  Mov_sensual(leg_ii,-grados_ii,-grados_ii/2);
  Mov_leg(leg_ii,grados_ii);
  Mov_sensual(leg_ii,-grados_ii,-grados_ii/2);
}
//////////////////////////////////////////////////////////////////////
//Moverse para adelante owo
//void Adelante(int pasos){
 // while(pasos <){
    
 // }
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ajustar la posicion de las patas para que queden segun las condiciones
//iniciales, ajustando el angulo que se forma entre la base y las patas
// centra base
void ajustar_pos_base(){

   hombro1.write(pos_h1_A);
   delay(15);
   hombro2.write(pos_h2_A);
   delay(15);
   hombro11.write(pos_h11_A);
   delay(15);
   hombro12.write(pos_h12_A);
   delay(15);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mov_sensual(Servo leg[],int grados, int GR){ 
  int pos_ini=leg[0].read();
  int pos_fin=pos_ini+grados;
    int Delta=pos_fin-pos_ini;
    int delta=GR/Delta;
  if (leg==leg1){
    Mov_leg_hombro(leg2,-grados);
    Mov_leg_hombro(leg4,grados);
    Mov_leg_pie(leg3,GR);
  }
  else if(leg==leg2){
    Mov_leg_hombro(leg1,-grados);
    Mov_leg_hombro(leg3,grados);
    Mov_leg_pie(leg4,GR);
  }
  else if (leg==leg3){
    Mov_leg_hombro(leg2,-grados);
    Mov_leg_hombro(leg4,grados);
    Mov_leg_pie(leg1,GR);
  }
  else if(leg==leg4){
    Mov_leg_hombro(leg1,-grados);
    Mov_leg_hombro(leg3,grados);
    Mov_leg_pie(leg2,GR);
  }
  delay(100);//
}
  

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Leg_Paso(Servo leg[],int grados){
  Mov_sensual(leg,20,10);
  delay(300);
  Mov_leg(leg,grados);
  delay(300);
  Mov_sensual(leg,-20,-10);
  delay(300);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Paso( int grados){
  Leg_Paso(leg1,grados);
  Leg_Paso(leg3,grados);
  Leg_Paso(leg2,grados);
  Leg_Paso(leg4,grados);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Gira movimiendo patas
void Girar(int grados,int delta_grados){
  int c = 0;
  // Si grados es mayor que delta_grados, se generaran rotaciones pequeñas 
  // de magnitud delta_grados cada una para no girar bruscamente.
  while(grados > delta_grados){
  Mov_2_leg(leg1,delta_grados,leg3,delta_grados);
  delay(1000);
  ajustar_pos_base();
  Mov_2_leg(leg2,delta_grados,leg4,delta_grados);
  delay(1000);
  ajustar_pos_base();
  //!!!!!!
  delay(1000);
  c +=1;
  grados -= delta_grados;}
  
  //luego se realiza una rotacion final para rotar la cantidad exacta de grados
  //requeridos                                                                                                                             
  Mov_2_leg(leg1,grados,leg3,grados);
  Mov_2_leg(leg2,grados,leg4,-grados);
  ajustar_pos_base();
  }
  

  // movimiento cangrejo
  // movimiento con sensor 
  

void loop(){
  delay(1000);
 Girar(30,15);

  
}
void Cosas(){ delay(300);
  Mov_sensual(leg1,30,20);
  delay(1000);
  Mov_sensual(leg1,-30,-20);
  Mov_leg_muslo(leg1,-40);
  Mov_sensual(leg1,-30,-20);
  delay(1000);
  Mov_sensual(leg1,30,20);
  Mov_leg_muslo(leg1,40);
  delay(1000);}
