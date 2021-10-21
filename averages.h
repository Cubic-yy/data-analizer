//--------------------------------------------------------------------------
/// @brief 平均を返します。
//--------------------------------------------------------------------------
/// @details 関数が呼ばれるごとにデータが蓄積され、蓄積されたデータの平均を返します。
//--------------------------------------------------------------------------
/// @param num 平均を求めたいデータ。
/// @param reset 蓄積されたデータを削除。
//--------------------------------------------------------------------------
/// @return 平均値
//--------------------------------------------------------------------------
float average(float num, int reset) {
    static float sum = 0;
    static int	cnt_function_called = 0;

    sum += num;
    cnt_function_called++;
    float num_average = sum / (float)cnt_function_called;		
    if (reset == 1) {
        sum = cnt_function_called = num_average = 0;
    }
    return num_average;
}

//--------------------------------------------------------------------------
/// @brief 区間長が1000の単純移動平均を返します。
//--------------------------------------------------------------------------
/// @details 関数が呼ばれるごとにデータが蓄積され、データ数が区間長に満たない場合は単なる
//	平均を返します。
//      例: 
//          float num
//          float array[10000] = {1, 2, 3, ...., 10000}
//          for (int i = 0; i < 10000; i++) {
//              num = moving_average(array[i]);
//              printf("現時点での移動平均 = %g" , num);
//          }
//--------------------------------------------------------------------------
/// @param num 単純移動平均を求めたいデータ。
/// @param reset 蓄積されたデータを削除。
//--------------------------------------------------------------------------
/// @return 単純移動平均または単なる平均。
//--------------------------------------------------------------------------
float moving_average(float num, int reset) {
    static int cnt_function_called = 0;
    static float sum_buf = 0;
    static float buf[1001] = {0};
    float num_average;

    buf[cnt_function_called%1001] = num;
    sum_buf = sum_buf + num - buf[cnt_function_called%1002];
    if (cnt_function_called < 1001) {
        num_average = sum_buf / (float)cnt_function_called;
    } else {
        num_average = sum_buf / 1000;
    }
    cnt_function_called++;
    if (reset == 1) {
        sum_buf = cnt_function_called = 0;
        for (int i = 0; i < 1001; i++) {
            buf[i] = 0;
        }
    }
    return num_average;
}
