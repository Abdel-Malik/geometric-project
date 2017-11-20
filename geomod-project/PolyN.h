#include <iostream>

class PolyN{
    private:


    public:
        float *coefs;
        PolyN *PolyNDeriv;
        int n;
        PolyN(float *coefs, int n);
        ~PolyN();
        PolyN* derivative();
        float val(float f);
        friend std::ostream &operator<<(std::ostream &, const PolyN &);

};
