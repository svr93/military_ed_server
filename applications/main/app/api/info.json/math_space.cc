#include "math_space.hpp" // SVR93
// SVR93

void get_sd_from_xyz (double t, double x,double y,double z, double& shirota, double& dolgota)
{
	double s; // угол поворота Земли
	double R;
	double R_xy;

	s=t*0.00007272205216643;
	R=sqrt(x*x+y*y+z*z);
	R_xy=sqrt(x*x+y*y);
   
	shirota=acos(R_xy/R);
	if (z<0.0) {shirota=-shirota;}

	dolgota=acos(x/R_xy);
	if (y<0.0) {dolgota=-dolgota;}
	dolgota=dolgota+s;
	if (dolgota>pi) {dolgota=dolgota-pi2;}
}

//--------------------------------------------------------------------------------------
void get_sd_from_xyz2d_Gr(double x,double y,double z, double& shirota, double& dolgota)
{
	double R;
	double R_xy;

	R=sqrt(x*x+y*y+z*z);
	R_xy=sqrt(x*x+y*y);
   
	shirota=acos(R_xy/R)*fDegreeInRadian;
	if (z<0.0) {shirota=-shirota;}

	dolgota=acos(x/R_xy);
	if (y<0.0) {dolgota=-dolgota;}
	
	shirota=shirota-(floor(shirota/90.0))*90.0;
	if (dolgota>pi) {dolgota=dolgota-pi2;}
	dolgota=dolgota*fDegreeInRadian;
}
//--------------------------------------------------------------------------------------
void get_sd_from_xyz2d (double t, double x,double y,double z, double& shirota, double& dolgota)
{
//    double s1=GMST(t);
    double R=sqrt(x*x+y*y+z*z);
    double R_xy=sqrt(x*x+y*y);
   
	shirota=acos(R_xy/R)*fDegreeInRadian;
	if (z<0.0) {shirota=-shirota;}

	dolgota=acos(x/R_xy);
	if (y<0.0) {dolgota=-dolgota;}

//	s1=s1-(floor(s1/pi2))*pi2;
//	dolgota=dolgota+s1;
	if (dolgota>pi) {dolgota=dolgota-pi2;}
	dolgota=dolgota*fDegreeInRadian;
}
//--------пересчет в координаты относительно земли----------------------------
void get_Zxyz_from_xyz(double t,double x,double y,double z,double& x_z,double& y_z,double& z_z)
{//t v sutkah
    double s1=GMST(t);//
	x_z=x*cos(s1)+y*sin(s1);
	y_z=-x*sin(s1)+y*cos(s1);
	z_z=z;
}
//------------------------------------
void get_sd_from_xyz (double th,double tm,double ts, double x,double y,double z, double& shirota, double& dolgota)
{
//	double s; // угол поворота Земли
	double R;
	double R_xy;
	
//	double t=(ts+tm*60.0+th*3600.0);
//	s=t*0.00007272205216643;
	R=sqrt(x*x+y*y+z*z);
	R_xy=sqrt(x*x+y*y);
   
	shirota=acos(R_xy/R);
	if (z<0.0) {shirota=-shirota;}

	dolgota=acos(x/R_xy);
//	if (y<0.0) {dolgota=-dolgota;}
//	dolgota = dolgota + s;
	if (dolgota>pi) {dolgota=dolgota-pi2;}
}

//------------------------------------------
double get_ygol_from_t (double t)
{ 
	return t*0.00007272205216643;
}
//------------------------------------------
double get_ygol_from_t_rad (double t)
{ 
	return t*0.00007272205216643*fDegreeInRadian;
}
//------------------------------------------
double get_t (int dd,int mm,int yy,double th,double tm,double ts)
{
	double t;
	double M[12]={0.0,31.0,59.0,90.0,120.0,151.0,181.0,212.0,243.0,273.0,304.0,334.0};
	
	int dy=yy-1958;		//годовая разница
	int vis;			//количество высокосных лет
	vis=floor(yy/4.0);
	
	int av=dy-vis*4;	//число лет после полных кварт

    if ((yy%4)==0)
	{	for(int i=2; i<12;i++)
		{
			M[i]=M[i]+1.0;
		}
	}
	t = ts + tm*60.0 + th*3600.0 + (M[mm-1]+dd)*86400.0 + 126230400.0*vis + 31536000.0*av + 86400.0*(floor(av/3.0));
    return t;

}

/* SVR93 double get_jd_fromdatetime (QDateTime dt)
{
    double jd=dt.date().toJulianDay();
    int hh=dt.time().hour();
    int mm=dt.time().minute();
    int ss=dt.time().second();
    int msec=dt.time().msec();
    jd = jd + ((double)hh+(double)mm/60.0+(double)ss/3600.00+(double)msec/3.6e6)/24.0-J_1957;
    return jd;

} SVR93 */
//------------------------------------------
/* SVR93 double get_t_fromdatetime (QDateTime dt)
{
	double t;
	
	int dd=dt.date().day();
	int mm=dt.date().month();
	int yy=dt.date().year();
	int th=dt.time().hour();
	int tm=dt.time().minute();
	double ts=dt.time().second();

	t=get_t (dd, mm, yy, th, tm, ts);
	return t;

} SVR93 */

//------------------------------------------
void get_hhmmss_from_t (int t,int& hh,int& mm,int& ss)
{
	ss=t%60;
	mm=(t/60)%60;
	hh=(t/3600)%24;   

}
//--------------------------------------------
double get_r_fromxyz(double x1,double y1,double z1,double x2,double y2, double z2)
{
	double r;
	r=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
	return r;
}
//-------получение пронормированных координат (x,y,z) по широте и долготе (s,d)--------
void get_xyz_from_sd_grad(double s,double d,double h,double& x,double& y,double& z)
{ 
	z=1.0*sin(s*fDegreeInGrad);
	x=1.0*sin(d*fDegreeInGrad);
	y=-1.0*cos(d*fDegreeInGrad);
}
//-------получение  координат (x,y,z) по широте и долготе (s,d)--------
void get_xyzR_from_sd_grad(double s,double d,double h,double& x,double& y,double& z)
{ 
	//z=R_Earth*sin(s*fDegreeInGrad);
	//x=R_Earth*sin(d*fDegreeInGrad);
	//y=-R_Earth*cos(d*fDegreeInGrad);

	x = R_Earth * cos(s*fDegreeInGrad) * cos(d*fDegreeInGrad);
    y= R_Earth * cos(s*fDegreeInGrad) * sin(d*fDegreeInGrad);
    z = R_Earth * sin(s*fDegreeInGrad);
}
//-------получение  координат (r,az,eps) простр-й точки(xс,yс,zс) относительно другой (x0,y0,z0)
void get_RAzEps_from_xyz(double& r, double& az, double& eps, double xc, double yc, double zc, double s0, double d0) // SVR93
{
   double xm,ym,zm;
   double x0, y0, z0; // SVR93
   get_xyzR_from_sd_grad(s0,d0,0.0,x0,y0,z0);
			

   r=get_r_fromxyz(xc,yc,zc,x0,y0,z0);
//----------------------
    double hi=0.0;
  //----------------
   double B =s0*fDegreeInGrad;// latitude;
   double L =d0*fDegreeInGrad;// longitude;
   double res00 = -sin(B)*cos(L)*cos(hi) - sin(L)*sin(hi);
   double res01 = -sin(B)*sin(L)*cos(hi) + cos(L)*sin(hi);
   double res02 = cos(B)*cos(hi);
   double res10 = cos(B)*cos(L);
   double res11 = cos(B)*sin(L);
   double res12 = sin(B);
   double res20 = sin(B)*cos(L)*sin(hi) - sin(L)*cos(hi);
   double res21 = sin(B)*sin(L)*sin(hi) + cos(L)*cos(hi);
   double res22 = -cos(B)*sin(hi);
  //----------------
	
	xm=res00*(xc-x0)+res01*(yc-y0)+res02*(zc-z0);
	ym=res10*(xc-x0)+res11*(yc-y0)+res12*(zc-z0);
	zm=res20*(xc-x0)+res21*(yc-y0)+res22*(zc-z0);

//   double rr=sqrt(xm*xm+ym*ym+zm*zm);
   double aa = sqrt( xm*xm+  ym*ym + zm * zm); // SVR93
   if (abs_my(aa) < 1e-6)
                eps = 0.0;
        else
                eps = asin(ym/aa);
   eps=eps*fDegreeInRadian;
//---------------
 
		 aa = sqrt(xm*xm + zm*zm);
        az = 0.0;
        if (aa > 1e-6)
                az = acos( xm / aa);
        if (zm < 0)/// верно
                az = 2*pi-az; // азимут в диапазоне 0..2*pi
		az=az*fDegreeInRadian;

}
//-------получение  координат (r,az,eps) простр-й точки(s,d,h) относительно другой (s0,d0,h0)
void get_RAzEps_from_sdh(double& r,double& az,double& eps,double s,double d,double h,double s0,double d0,double h0)
{
  	double x0,xc,y0,yc,z0,zc;
	get_xyzR_from_sd_grad(s0, d0, h0,x0,y0,z0);
	get_xyzR_from_sd_grad(s, d, h,xc,yc,zc);
	r=get_r_fromxyz(xc,yc,zc,x0,y0,z0);
	eps=0.0;	// неправильно  
	//az=get_azim_from_sd(s0,d0,s,d);

}
//--------------------------------------------------------------------
double abs_my(double val)
{
 if (val<0) return -val;
 else return val;
}

//--------расчет положения ракеты на момент времени - t
void get_rocet_xyz_from_t(int tip_tr ,double t,double s_start,double d_start,double s_end,double d_end,double& x,double& y,double& z)
{
	double fi;		// угол - fi между стартом и падением
	double fi_2;
	double delta_s,delta_d;
	double dd;
	double L;		// дальность полета
	double T_sum;	// время полета
	double DE;
	double lam;
	double ha;		// высота апогея
	double ex;		// эксцентриситет орбиты
	double a;		// большая полуось
	double x_start,y_start,z_start;
	double x_end,y_end,z_end;
	double aa,bb,cc;
	double rr;
	double i;		// наклонение орбиты
	double dvu;		// долгота восходящего узла
	double w;		// аргумент перигея
	double w_st,w_end;
	double u;		//аргумент широты орбиты

	s_start=s_start*fDegreeInGrad;
	d_start=d_start*fDegreeInGrad;
	s_end=s_end*fDegreeInGrad;
	d_end=d_end*fDegreeInGrad;

  //--- опред угол - fi между стартом и падением
	delta_s=s_end-s_start;
	delta_d=d_end-d_start;
	dd=sin(delta_s)*sin(delta_s)+sin(delta_d)*sin(delta_d);

	if (delta_s>(pi/2.0) || delta_d>(pi/2.0))
		{
			fi=pi-2*asin(sqrt(dd)/2.0);
		}
	else 
		{
			fi=2*asin(sqrt(dd)/2.0);
		}

	//--- расчет дальность полета
	L=fi*R_Earth;

	//--- расчет времени полета для опт траектории в сек
	T_sum=22.0*L/(sqrt(L)+15.0);

	//--- учет фактора вращения Земли
	DE=T_sum*V_ugl;
	lam=DE*cos(s_end);
	d_end=d_end+lam;

	//--- расчет высоты апогея - ha
	fi_2=fi/2.0;
	ha=(R_Earth/2.0)*(sin(fi_2)+cos(fi_2)-1.0);

	//--- расчет эксцентриситета орбиты - ex
	ex=ha/(ha+R_Earth*(1-cos(fi_2)));

	//--- расчет большой полуоси орбиты - a
	a=(R_Earth+ha)/(1+ex);

	//--- расчет наклонения орбиты - i
	x_start=R_Earth*cos(s_start)*cos(d_start);
	y_start=R_Earth*cos(s_start)*sin(d_start);
	z_start=R_Earth*sin(s_start);

	x_end=R_Earth*cos(s_end)*cos(d_end);
	y_end=R_Earth*cos(s_end)*sin(d_end);
	z_end=R_Earth*sin(s_end);

	aa=y_start*z_end-z_start*y_end;
	bb=z_start*x_end-x_start*z_end;
	cc=x_start*y_end-y_start*x_end;
	
	cc=abs_my(cc);
	rr=sqrt(aa*aa+bb*bb+cc*cc);
	i=acos(cc/rr);
	if (delta_d<0.0) i=pi-i;

	//--- расчет долготы восходящего узла - dvu
	dvu=acos(-bb/sqrt(aa*aa+bb*bb))-t*V_ugl;
	if (delta_d<0.0) dvu=pi+dvu;

	//--- расчет аргумента перигея орбиты - w
	w_st=acos((aa*x_start+bb*y_start)/R_Earth);
	w_end=acos((aa*x_end+bb*y_end)/R_Earth);
	w=(w_st+w_end)/2.0-pi;

	//--- расчет аргумента широты арбиты - u
	u=s_start;	

}
//-------------------------------------------------------------
///               Расчет звездного времени на гринвиче                                              ///
///                                                                                                 ///
/// ВХОД:  t - [сутки] в JD1957                                                                     ///
/// ВЫХОД: GMST() -  [rad] звездное время на гринвиче в радианах                                    ///
///                                                                                                 ///
/* SVR93 double GMST(double t)
{
//1.Вычисление модифицированной  юлианской даты на начало суток
    double JD = t + J_1957 ;
    QDate dt_temp1 = QDate::fromJulianDay( JD );// Юлианская дата с -4713г. до н.э.
    QTime time_tmp(0, 0, 0);
    double n_sec_left = ( JD - floor( JD ) ) * fSecondsInDay;
    time_tmp = time_tmp.addSecs( n_sec_left );

    double Year = dt_temp1.year();
    double Mon = dt_temp1.month();
    double Day = dt_temp1.day();
    double Var2;
// вычисление мод.юл.даты
double Var1 = 10000 * Year + 100 * Mon + Day;
if (Mon <= 2) { Mon = Mon + 12; Year = Year - 1 ; }
if (Var1 <= 15821004.1)//здесь учтено, что после 4,10,1582 следует 15,10,1582
    Var2 = -2 + floor( ( Year + 4716 )/4 ) - 1179;
else
    Var2 = floor( Year/400 ) - floor( Year/100 ) + floor( Year/4 );
double Var3 = 365.0 * Year - 679004.0 ;
double MD = Var3 + Var2 + floor(306001 * ( Mon + 1 ) / 10000) + Day ;//MD на 0h
//MD = Var3 + Var2 + 306001 * (Mon + 1) \ 10000 + Day
// \ - деление нацело
// SVR93 MD = JD - 2400000.5
// SVR93 0 часов 17.11.1858 г.

//2. Вычисление звездного времени

double T0 = (MD - 51544.5) / 36525;//мод.юл.дата на начало суток в юлианских столетиях
// SVR93 MD 0 часов 17.11.1858 г.
double a1 = 24110.54841 ;       //[s]
double a2 = 8640184.812866 ;    //[s]
double a3 = 0.093104 ;          //[s]
double a4 = 0.0000062 ;         //[s]
double S0 = a1 + a2 * T0 + a3 * T0*T0 - a4 * T0*T0*T0;// звездное время на Гринвиче на начало суток в секундах
double Nsec = n_sec_left;//количество секунд, прошедших  от начала суток до момента наблюдения//50400
//double Nsec = UT * 3600 ;
//UT - всемирное время в часах, момент расчета
double NsecS = Nsec * 366.2422 / 365.2422;//количество звездных секунд //50537.9906264939
double SG = (S0 + NsecS) / 3600 ;//[h] гринв.сред.зв.время в часах
if (SG < 0) SG += 24 ;//[h] _ проверить ????
// double ST = SG + Lon ;// местное звездное время
//Lon – долгота наблюдателя
SG = SG / 24 ;// [сутки] - vremya v sutkah
return SG * 2 * pi ;// [rad]

} SVR93 */
double GMST(double t) { return V_ugl * t * fSecondsInDay; } // SVR93

//------------------------------------------------------------
/// пересчет долготы L , широты B  и высоты h в HСК (xg, yg, zg)
/// вход double L(рад), B(рад), h(метры)
/// выход X, Y, Z (неподв СК);(метры)
void LBtoNSK(double& dolgota, double& shirota, double& h, double& t, double& Xnsk, double& Ynsk, double& Znsk)
{
    double Xgsk, Ygsk, Zgsk;
    LBtoGSK(dolgota,shirota,h,Xgsk,Ygsk,Zgsk);
    GSKtoNSK(Xgsk,Ygsk,Zgsk, Xnsk,Ynsk,Znsk, t);
    return;
}

//-----------------------------------------------------------------
/// пересчет долготы L , широты B  и высоты h в ГСК (xg, yg, zg)
/// вход double L(рад), B(рад), h(метры)
/// выход X, Y, Z ;(метры)
void LBtoGSK(double& dolgota, double& shirota, double& h, double& Xgsk,double& Ygsk,double& Zgsk)
{
    Xgsk=(Rz+h)*cos(shirota)*cos(dolgota);
    Ygsk=(Rz+h)*cos(shirota)*sin(dolgota);
    Zgsk=(Rz+h)*sin(shirota);
    return;
}

//------------------------------------------------------------------
/// X,Y,Z nsk и X,Y,Z gsk; (метры)
void GSKtoNSK(double & Xgsk, double & Ygsk, double & Zgsk, double & Xnsk, double & Ynsk, double & Znsk, double& t)
{
    double szv = GMST(t);
//        S1(0, 0) =  cos(szv); S1(0, 1) = -sin(szv); S1(0, 2) = 0;
//        S1(1, 0) =  sin(szv); S1(1, 1) = cos(szv);  S1(1, 2) = 0;
//        S1(2, 0) = 0; S1(2, 1) = 0; S1(2, 2) = 1;
    Xnsk =  Xgsk*cos(szv)-Ygsk*sin(szv);
    Ynsk =  Xgsk*sin(szv)+Ygsk*cos(szv);
    Znsk =  Zgsk;
//    XYZnsk = S1 * XYZgsk;
    return;
}
//------------------------------------------------------------------
/// X,Y,Z nsk и X,Y,Z gsk; (метры)
void NSKtoGSK(double & Xnsk, double & Ynsk, double & Znsk,double & Xgsk, double & Ygsk, double & Zgsk,  double& t)
{
    double szv = GMST(t);//sutki
//        S1(0, 0) =  cos(szv); S1(0, 1) = sin(szv); S1(0, 2) = 0;
//        S1(1, 0) =  -sin(szv); S1(1, 1) = cos(szv);  S1(1, 2) = 0;
//        S1(2, 0) = 0; S1(2, 1) = 0; S1(2, 2) = 1;
    Xgsk =  Xnsk*cos(szv)+Ynsk*sin(szv);
    Ygsk = -Xnsk*sin(szv)+Ynsk*cos(szv);
    Zgsk =  Znsk;
    return;
}
//-------
double ABS(double x)
{
    if(x>=0)
        return x;
    else
        return -x;
}
//-----------------------------------------------------
double Xcub(double x)
{
    return pow(x, 3);
}

void PodsputnTochka(double& aosk, double& e, double& nakl, double& dby, double& w, double& tper, double& t, double& D, double& S )
{//Rz, rad,sutki(jd57)
    /// вычисление широты u в момент времени t, t и Tper должны быть в сутках
    double a=aosk;//rad
    double i=nakl;//rad
    double dvu=dby;//rad
    double omega_peri=w;
    double tau_per=tper;//sutki
    double n_cp = sqrt(Mu / Xcub(a) );//среднее движение (sutki, Rz)
    double M = n_cp * (t - tau_per);//средняя аномалия на момент t
    M = M - floor( M / pi2 ) * pi2;//rad

    double E1 = 0;
    if( M > pi)  E1 = M - e;
    else         E1 = M + e;

    double E2 = 10;
    bool bFlag = false;

    while( ABS(E2 - E1) > 1e-9 )//суть: зная М, найти Е.
    {
        if(bFlag)  E1 = E2;

        E2 = E1 - (E1 - e * sin(E1) - M)/(1 - e * cos(E1));

        if (!bFlag)
            bFlag = true;
    }

    E1 = E2 - floor( E2 / pi2 ) * pi2;

    double anom = 2 * atan( sqrt( (1+e) / (1-e) ) * tan( E1 / 2 ));
    if (anom < 0)
        anom += pi2 ;

    double u = omega_peri + anom;
    double E = E1;

    if ( u > pi2) u -= pi2;
    else
        if ( u < 0) u += pi2;

    double r = a  * (1 - e * cos(E));
    double x = r * (cos(dvu) * cos(u) - sin(dvu) * sin(u) * cos(i));
    double y = r * (sin(dvu) * cos(u) + cos(dvu) * sin(u) * cos(i));
    double z = r * sin(u) * sin(i);
    double xGSK, yGSK, zGSK;
    double xn=x*Rz;/// в метрах
    double yn=y*Rz;
    double zn=z*Rz;
    NSKtoGSK(xn, yn,zn, xGSK, yGSK, zGSK, t);/// m, sutki
    double Long = 0;
    double Lat = 0;
    double R = sqrt(xGSK*xGSK+yGSK*yGSK+zGSK*zGSK);
    double xy = sqrt(xGSK*xGSK+yGSK*yGSK);
    if (R > 1e-6)
        Lat=asin(zGSK/R);
    if (xy > 1e-6)
    {
        Long=acos(xGSK/xy);
        if (yGSK<0)//y<0
        {
            Long=pi2-Long;
        }
    }
    D=Long;
    S=Lat;
    return;

}

double RAD(double x)
{
    return x/fDegreeInRadian;
}

//------расчет кепл элем орбиты ракеты по точке старта и падения
/// входные данные
/// долгота, широта старта (градусы), долгота , широта падения (градусы), время старта
/// выходные данные
/// кеплеровы элементы на момент времени t (double t - jd57  в сутках)
void get_EO_from_StartFinishSD(double t, double Sstart, double Dstart, double Send, double Dend, double& tend, double& a, double& e, double& i, double& dvu, double& omega_per, double& tper, double& u)
{// a in km, i, dvu, omega in degrees
    bool bUtochVrem=true;
    double DOLGOTA_START_DEG = Dstart;/// формат 00.0 градусы
    double SHIROTA_START_DEG = Sstart;//= 0.0;/// формат 00.0 градусы
    double DOLGOTA_END_DEG = Dend;//= 90.0;/// формат 00.0 градусы
    double SHIROTA_END_DEG = Send;// = 89.0;/// формат 00.0 градусы
    double tstart;
    tstart=t;

    double DOLGOTA_START ;//= RAD(DOLGOTA_START_DEG);/// формат 00.0 градусы
    double SHIROTA_START ;//= RAD(SHIROTA_START_DEG);/// формат 00.0 градусы
    double DOLGOTA_END ;//= RAD(DOLGOTA_END_DEG);/// формат 00.0 градусы
    double SHIROTA_END;// = RAD(SHIROTA_END_DEG);/// формат 00.0 градусы

    double teta = RAD(20.0);
    const double epsilon=0.01/fSecondsInDay;
    double t2_prev=epsilon+0.1;
    double t2;

    SHIROTA_START_DEG=Sstart;
    DOLGOTA_START_DEG=Dstart;
    while(DOLGOTA_START_DEG<0)
        DOLGOTA_START_DEG=DOLGOTA_START_DEG+360;
    if(SHIROTA_START_DEG==0)
        SHIROTA_START_DEG=SHIROTA_START_DEG+1e-6;
    if(ABS(SHIROTA_START_DEG)==90)
        SHIROTA_START_DEG=SHIROTA_START_DEG/ABS(SHIROTA_START_DEG)*(ABS(SHIROTA_START_DEG)-1e-6);
    SHIROTA_START=RAD(SHIROTA_START_DEG);
    DOLGOTA_START=RAD(DOLGOTA_START_DEG);

    SHIROTA_END_DEG=Send;
    DOLGOTA_END_DEG=Dend;
    if(DOLGOTA_END_DEG<0)
        DOLGOTA_END_DEG=DOLGOTA_END_DEG+360;
    if(SHIROTA_END_DEG==0)
        SHIROTA_END_DEG=SHIROTA_END_DEG+1e-6;
    if(ABS(SHIROTA_END_DEG)==90)
        SHIROTA_END_DEG=SHIROTA_END_DEG/ABS(SHIROTA_END_DEG)*(ABS(SHIROTA_END_DEG)-1e-6);
    if(SHIROTA_END_DEG==-SHIROTA_START_DEG )
    {
        SHIROTA_END_DEG+=0.9;
        SHIROTA_START_DEG-=0.9;
        DOLGOTA_END_DEG+=0.9;
        DOLGOTA_START_DEG-=0.9;
    }
    SHIROTA_END=RAD(SHIROTA_END_DEG);
    DOLGOTA_END=RAD(DOLGOTA_END_DEG);

    double dl = DOLGOTA_END - DOLGOTA_START;
    if(dl>pi)
        dl-=2*pi;

    /// Найдем координаты (.) R1 в NSK на момент tstart
    double x1, y1, z1;
    double htmp1=0.0;
    LBtoNSK( DOLGOTA_START, SHIROTA_START, htmp1, tstart, x1, y1, z1);

m1:

    /// Найдем координаты (.) R2 в NSK
    double x2, y2, z2;
    if(bUtochVrem)//на момент t_start
        LBtoNSK( DOLGOTA_END, SHIROTA_END, htmp1, tstart, x2, y2, z2);
    else// на момент t2=t_start+dt;
        LBtoNSK( DOLGOTA_END, SHIROTA_END, htmp1, t2, x2, y2, z2);

    double beta=acos((x1*x2+y1*y2+z1*z2)/Rz/Rz)/2;
    double beta_grd = beta*fDegreeInRadian;
    if(beta_grd>80)
    {
//        QMessageBox::about(this, QString::fromLocal8Bit("Ошибка!"),
//                           QString::fromLocal8Bit("Допустимая дальность должна быть не более 120 градусов!")) ;
//        return;
    }
    double alfa = 2*teta;
    double gamma = pi - alfa - beta;
    a = (Rz*(sin(beta)/sin(gamma)+1))/2;
    double c = Rz*sin(alfa)/2/sin(gamma);
    double ex = c/a;
    int caseidvu=0;
    a=a/Rz;// in Rz

    /// Находим широту апогея Adx - угол от оси х до направления на апогей
    /// (в инерциальной СК ) - середина отрезка х1 х2, но длина его Ra!
    double dx=(x1+x2)/2;
    double dy=(y1+y2)/2;
    double dz=(z1+z2)/2;
    double dR=sqrt(dx*dx+dy*dy+dz*dz);// середина отрезка х1 х2

    /// плоскость проходящая через три точки х1 и х2 и начало координат
    /// А,В и С проекции перпендикуляра опроведенного к плоскости на оси
    /// ох оу оз
    double A = y1*z2-z1*y2;
    double B = z1*x2-x1*z2;
    double C = x1*y2-y1*x2;

    /// наклонение (угол м/у 2мя плоскостями)
    i=acos(ABS(C)/sqrt(A*A+B*B+C*C));/// (0; pi)

    /// долгота восходящего узла
    double dvut;
    double arg = -A / B ;/// через уравнения прямой на плоскости
    dvut = atan( arg );

    double xdvu,ydvu;

m3:
    xdvu=Rz*cos(dvut);
    ydvu=Rz*sin(dvut);

    if(dz>0)
        omega_per=pi+acos((dx*xdvu+dy*ydvu)/dR/Rz);
    else
        omega_per=pi-acos((dx*xdvu+dy*ydvu)/dR/Rz);

    double igrd=i*fDegreeInRadian;
    double dvutgrd= dvut*fDegreeInRadian;
    double omega_pergrd=omega_per*fDegreeInRadian;
    /// аномалия всегда определяется правильно, т.к.
    /// между х1 - dx всегда меньше 180
    double anom1=pi-acos((x1*dx+y1*dy+z1*dz)/Rz/dR);
    //    double u1 = acos((x1*dx+y1*dy+z1*dz)/Rz/dR);
    double u1 = anom1 + omega_per;
    double ugrd= u1*fDegreeInRadian;
    double tmp = tan(anom1/2) * sqrt((1-ex)/(1+ex)) ;
    double E1 = 2*atan(tmp);
    double M1 = E1 - ex*sin(E1);
    double ncp = sqrt(Mu / pow(a, 3) ) ; //среднее движение
    tper = tstart - M1/ncp ;
//    double dt_start_peri_min = (tstart-tper)*fSecondsInDay/60 ;
    double anom2 = 2*pi - anom1 ;
    tmp = tan(anom2/2) * sqrt((1-ex)/(1+ex)) ;
    double E2 = 2*atan(tmp);

    while(E2<E1)
        E2 = E2+2*pi;

    double M2 = E2 - ex*sin(E2);
    t2 = tper + M2/ncp;
//    double deltat = t2 - tstart;
    double deltat2 = t2_prev - t2;

    while( ABS(deltat2) > epsilon )
    {
        t2_prev=t2;
        bUtochVrem=false;
        goto m1;
    }

    /// находим подспутниковую точку на момент времени t_start
//m2:
    /// сравниваем долготу и широту подспутниковой точки с заданными
    double L;
    PodsputnTochka(a, ex, i, dvut, omega_per, tper, t2, L, B);//Rz, rad,sutki(jd57)
    double deltaLp=L-DOLGOTA_END;//rad
    PodsputnTochka(a, ex, i, dvut, omega_per, tper, tstart, L, B);
    double deltaLs=L-DOLGOTA_START;//rad

    while(deltaLs>pi)
        deltaLs-=2*pi;
    while(deltaLs<-pi)
        deltaLs+=2*pi;
    while(deltaLp>pi)
        deltaLp-=2*pi;
    while(deltaLp<-pi)
        deltaLp+=2*pi;

    if(ABS(deltaLs)>1/fDegreeInRadian
            || ABS(deltaLp)>1/fDegreeInRadian)
    {/// нужно скорректировать наклонение  и дву
        if(caseidvu==0)
        {
            if(dvut>=pi) dvut-=pi;
            else dvut+=pi;
            caseidvu++;
            goto m3;
        }
        else
            if(caseidvu==1)
            {
                if(dvut>=pi) dvut-=pi;
                else dvut+=pi;
                i=pi-i;
                caseidvu++;
                goto m3;
            }
            else
                if(caseidvu==2)
                {
                    if(dvut>=pi) dvut-=pi;
                    else dvut+=pi;
                    caseidvu++;
                    goto m3;
                }
                else
                    if(caseidvu==3)
                    {
                        /// взять те параметры, при которых дельта минимальная
                    }
    }

    a=a*Rz*1e-3;//km
    e=ex;
    i=igrd;//degrees
    dvu=dvutgrd;//?
    omega_per=omega_pergrd;//degrees
    u=ugrd;//degrees
    tend=t2+30/fSecondsInDay;//JD

}

//-------------------------------------------
void get_ko_xyz_from_t(double t,double a,double e,double naklon,double DBY,double omega_per,double tper, double& x,double& y,double& z)
{  
//t in sutki, a in km, i, omega, w in grad
    double w=RAD(omega_per);
    double omega=RAD(DBY);
    double i=RAD(naklon);

    double n_medium=sqrt(MU_km_s/(a*a*a));//kilometers and seconds
    //	double E0=2.0*atan(sqrt((1.0-e)/(1.0+e)))*tan(-w/2.0);
    //	double tt=(E0-e*sin(E0))/n_medium + t0;

    double M=n_medium*(t-tper)*fSecondsInDay;
    M=M-floor(M/pi2)*pi2;
    double EE;
    double E1;
    double delta;

    E1=(M>pi)?M-e:M+e;
    EE=10.0;
    //    bool bFlag=false;
    delta=abs_my(EE-E1);

    while(delta>1e-9)
    {
        EE=E1-(E1-e*sin(E1)-M)/(1.0-e*cos(E1));
        E1=EE;
        delta=abs_my(EE-E1);
    }

    EE=EE-(floor(EE/pi2))*pi2;

    double v;

    v=2.0*atan(sqrt((1.0+e)/(1.0-e))*tan(EE/2.0));
    if (v < 0)
        v += pi2 ;

    double u=w+v;

    double R=a*(1.0-e*cos(EE));

    x=R*(cos(omega)*cos(u)-sin(omega)*sin(u)*cos(i));
    y=R*(sin(omega)*cos(u)+cos(omega)*sin(u)*cos(i));
    z=R*sin(u)*sin(i);
}
