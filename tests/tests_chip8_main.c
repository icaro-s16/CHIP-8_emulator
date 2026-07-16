#include <CUnit/Basic.h>
#include "tests_chip8_decoder.c"
#include "tests_chip8_emulator.c"
#include "tests_chip8_executer.c"


int main(){
    if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
    
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("chip8_test_suite", 0, 0);
    
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test_decoder_set_register_op", test_decoder_set_register_op)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "test_decoder_set_doubleregister_op", test_decoder_set_doubleregister_op)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "test_decoder_set_address_op", test_decoder_set_address_op)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite, "test_decoder_function", test_decoder_function)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_suite(pSuite);
    
    CU_cleanup_registry();
    
    return CU_get_error();
}
