/*
* Federal values
*/
/*rates*/
#define F_RATE1 0.16
#define F_RATE2 0.22
#define F_RATE3 0.26
#define F_RATE4 0.29

/*Base Amount*/
#define F_BASE1 0
#define F_BASE2 35000
#define F_BASE3 70000
#define F_BASE4 113804

/*Taxable Base Amount*/
#define F_TBASE1 0
#define F_TBASE2 5600
#define F_TBASE3 13300
#define F_TBASE4 24689

#define F_TCRD_RATE 0.16        /*Total Tax Credit Rate*/
#define F_BEXEMP 8012           /*Basic Exemption*/

/*Limits for various Income values*/
#define F_LIMIT1 35000
#define F_LIMIT2 70000
#define F_LIMIT3 113804

/*Limits for CPP and EI values -defined by federal govrmt*/
#define CPP_MAX 1831.50
#define EI_MAX 772.20

/*
* Ontario values
*/
/*rates*/
#define O_RATE1 0.0605
#define O_RATE2 0.0915
#define O_RATE3 0.1116

/*base amount*/
#define O_BASE1 0
#define O_BASE2 33375
#define O_BASE3 66752

/*taxable base amount*/
#define O_TBASE1 0
#define O_TBASE2 2019
#define O_TBASE3 5073

#define O_TCRD_RATE 0.0605      /*Ontario Tax Credit Rate*/
#define O_BEXEMP 8044           /*Ontario Basic Exemption*/

#define B_RDTN 186      /*Basic Reduction*/
#define DEPDT 343       /*Dependants*/

/*surtaxes*/
#define SURTAXA 3856
#define SURTAXA_PRCT 0.20
#define SURTAXB 4864
#define SURTAXB_PRCT 0.36

/*Income Limits*/
#define O_LIMIT1 33375
#define O_LIMIT2 66752

/*******Function Prototypes*******/
/*---Buffer Clear---*/
void bufferClear(void);

/*---Input Validation---*/
double InputValid(double value,int count,double Inc_14,double CPP_16,double EI_18, int x_menu);

/*---Fed_Conditions---*/
void Fed_Conditions(double Inc_14, double *rate, double *base, double *Tbase);

/*---Ont_Conditions---*/
void Ont_Conditions(double Inc_14, double *rate, double *base, double *Tbase);

/*---CPP_EI_Restrictions---*/
void CPP_EI_Restrictions(double *cppOvrp, double *cpp, double *eiOvrp, double *ei);

/*---Results---*/
void results(double *Inc_14, double *CPP_16, double *EI_18, double *Inc_Tax_Ddct_22, double *Stk_Opt_41, double *Un_Dues44, int *Nod, double *F_rate, double *F_base, double *F_Tbase, double *O_rate, double *O_base, double *O_Tbase, double *EI_Ovrp, double *CPP_Ovrp);

/*---SigDigs---*/
double SigDigs(double value);

/*---diffRestriction---*/
void diffRestriction(double diff, double Owing, double refund);

