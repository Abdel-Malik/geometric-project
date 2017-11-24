#include <iostream>

class PolyN{
    private:


    public:
        float *coefs;
        PolyN *PolyNDeriv;
        int n;
        PolyN();
        PolyN(int n);
        PolyN(float *coefs, int n);
        ~PolyN();
        PolyN* derivative();
        float val(float f);
        void editCoef(int n,float f);
        friend std::ostream &operator<<(std::ostream &, const PolyN &);

};
