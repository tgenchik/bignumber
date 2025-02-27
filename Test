#include "LongNumber.hpp"
#include <cassert>
void testAddition() {

    LongNumber a("788923489238238321781201902190120");  
    LongNumber b("832616727367126732167321632193102043324176431836729101");
    LongNumber result = a + b;
    assert(result.toString() == "832616727367126732168110555682340281645957633738919221");  

    LongNumber c("-8829415895002903528051847651578957689"); 
    LongNumber d("987654321");   
    LongNumber result2 = d + c;
    assert(result2.toString() == "-8829415895002903528051847650591303368"); 

    LongNumber e = 183819.682_longnum;  
    LongNumber f = 2044.1331_longnum;  
    LongNumber result3 = e + f;
    assert(result3.toString(4) == "185863.8151");  

    std::cout << "OK\n";
}

void testSubtraction() {
   
    LongNumber a("1509158053829389421"); 
    LongNumber b = 123456789.2_longnum;  
    LongNumber result = a - b;
    assert(result.toString(1) == "1509158053705932631.8");  

    
    LongNumber c = 8423934.4387_longnum;  
    LongNumber d("8417408237127081237308124370843218174");   
    LongNumber result2 = c - d;
    assert(result2.toString(4) == "-8417408237127081237308124370834794239.5613");  

    
    LongNumber e("761347965084343701378012657238154067741475611047481746570145546541054754756413413717641718141761754614314");  
    LongNumber f("401738248517423745865015875346824560124356812835382759831953616953");  
    LongNumber result3 = e - f;
    assert(result3.toString() == "761347965084343701378012657238154067741073872798964322824280530665707930196289056904806335381929800997361");  
    std::cout << "OK\n";

}

void testMultiplication() {
    LongNumber a = 17.456_longnum;  
    LongNumber b = -13.87_longnum;     
    LongNumber result = a * b;
    assert(result.toString(5) == "-242.11472");  

    LongNumber c("-803247324834021037842783427178403278428");  
    LongNumber d("7483874187187812487824178124184034870510");   
    LongNumber result2 = c * d;
    assert(result2.toString(4) == "-6011401920252993982941750281656968397523373671338715615524990171086056456358280");

    std::cout << "OK\n";
}


void testComparison() {
   
    LongNumber a("83424824378023218342013243412028537");  
    LongNumber b("83424824378023218342013243412028538");  
    assert(a < b);
    assert(b > a);
    assert(a != b);

    
    LongNumber c("-9999999972");  
    LongNumber d("-9999999999");  

    assert(c > d);
    assert(d < c);
    assert(c != d);

   
    LongNumber e = -1;  
    LongNumber f = 1;  
    assert(e < f);
    assert(f > e);
    assert(e != f);
    std::cout << "OK\n";
}
void testDivision() {
   
    LongNumber a("333");  
    LongNumber b("999999999999999999999999999");  
    LongNumber result = b / a;
    assert(result.toString() == "3003003003003003003003003");  

    LongNumber c = 16.3132_longnum;  
    LongNumber d = 18734.39192_longnum;  
    LongNumber result2 = d / c;
    assert(result2.toString(12) == "1148.419189368119"); 

    std::cout << "OK\n"; 
}

int main() {
    testAddition();
    testSubtraction();
    testMultiplication();
    testComparison();
    testDivision();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
