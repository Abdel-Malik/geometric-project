#include <iostream>
#include <vector>

class PolyN{
    private:

    public:
        std::vector<float> coefs;
        PolyN *PolyNDeriv;
        int n;
        PolyN();
        PolyN(int n);
        PolyN(float *coefs, int n);
        ~PolyN();
        PolyN* derivative();
        float val(float f);
        void editCoef(int n,float f);
        void addCoef(float f);
        friend std::ostream &operator<<(std::ostream &, const PolyN &);

};
