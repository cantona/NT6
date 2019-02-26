// naihe 05-8-16 13:18
//    自從 2003-04-29 使用 ctime_new() 函數以來，一直覺得有些不爽
//    今天改成新的方式，兼容舊的，新的更好！
#include "localtime.h"
#define        LT_MON_ADD            1        // 有些OS存在這個BUG，沒有把 LT_MON 加一，可以修正一下
#define        DEFAULT_FORMAT_STR    "YY.M.D(w) h:m:s"  // 默認標準表述格式

string ctime_format_help()
{
    string msg;
    msg = "\n"
    + "varargs string ctime_format( mixed arg1, mixed arg2 ) 幫助：\n"
    + "----------------------------------------------------------------------\n"
    + "函數説明：根據自定義的格式，把一個時間數字所代表的時間信息表述出來。\n"
    + "          (返回 string 信息)\n"
    + "傳入參數：1、(string) 格式規範(sFormat)\n"
    + "          2、(int) 欲查詢的時間(iTime)\n"
    + "兼容：    自由傳入參數，使代碼編寫更方便。\n"
    + "          規則：1、省略參數時，得到當前時間的默認格式表述；\n"
    + "                2、只傳入 (int) iTime 時，使用默認格式表述；\n"
    + "                3、只傳入 (string) sFormat 時，使用當前時間表述；\n"
    + "                4、兩個參數都傳入時，根據你的設置表述。\n";
    msg += ""
    + "格式規範：["+DEFAULT_FORMAT_STR+"] 是標準的格式，其中：\n"
    + "           YY 將被替換成為年份的數字如：2005\n"
    + "           Y  優先替換 YY 之後，Y 將被替換為短年份格式如：05\n"
    + "           M  將被替換成為月份的數字如：02, 11\n"
    + "           D  將被替換成為日期的數字如：08, 31\n"
    + "           w  將被替換成為星期的漢字如：三，日，六\n"
    + "           h  將被替換成為小時的數字如：01, 24\n"
    + "           m  將被替換成為分鐘的數字如：01, 58\n"
    + "           s  將被替換成為秒鐘的數字如：08, 59\n";
    msg += ""
    + "           根據以上規律，你可以自定需要的格式，例如：\n"
    + "           ctime_format( \"Y-M-D h:m:s 星期w\",1124174889 )  即得出：\n"
    + "               05-08-16 14:48:09 星期二  這種非規範的格式。\n"
    + "----------------------------------------------------------------------\n";
    return msg;
}

string i_to_s( int num )
{
    if( num == 0 )
        return "00";
    if( num < 10 )
        return sprintf( "0%d", num );
    return sprintf( "%d", num );
}
// 這是真正的檢測函數。喜歡的話，也可以直接調它；但是還是經過檢測的安全些吧。
string ctime_format_real( int iTime, string sFormat )
{
    mixed *lt;
    string wday;
    if( !iTime || !sFormat )
        return 0;
    lt = localtime( iTime );
    if( !lt || !sizeof(lt) )
        return 0;
    // 獲得星期幾的中文
    wday = chinese_number( lt[ LT_WDAY ] );
    if( lt[ LT_WDAY ] == 0 )
        wday = "日";
    sFormat = replace_string( sFormat, "YY", i_to_s(lt[LT_YEAR]) );      // 注：這句要在 Y 前
    sFormat = replace_string( sFormat, "Y", (lt[LT_YEAR]+"")[2..<1] );   // 注：這句要在 YY 後
    sFormat = replace_string( sFormat, "M", i_to_s(lt[LT_MON]+LT_MON_ADD) );
    sFormat = replace_string( sFormat, "D", i_to_s(lt[LT_MDAY]) );
    sFormat = replace_string( sFormat, "w", wday );
    sFormat = replace_string( sFormat, "h", i_to_s(lt[LT_HOUR]) );
    sFormat = replace_string( sFormat, "m", i_to_s(lt[LT_MIN]) );
    sFormat = replace_string( sFormat, "s", i_to_s(lt[LT_SEC]) );
    return sFormat;
}

varargs string ctime_format( mixed arg1, mixed arg2 )
{
    string sFormat;
    int iTime;
    
    // 忽略2個參數時，即以默認格式獲得當前時間的表述
    if( !arg1 && !arg2 )
    {
        return ctime_format_real( time(), DEFAULT_FORMAT_STR );
    }
    // 忽略第二個參數時
    if( arg1 && !arg2 )
    {
        if( stringp(arg1) )
        {
            sFormat = arg1;
            iTime = time();
        }
        else if( intp(arg1) && arg1 > 0 )
        {
            iTime = arg1;
            sFormat = DEFAULT_FORMAT_STR;
        }
        else
            return 0;
    }
    // 忽略第一個參數時(例如傳入 0, 1)
    if( !arg1 && arg2 )
    {
        if( stringp(arg2) )
        {
            sFormat = arg2;
            iTime = time();
        }
        else if( intp(arg2) && arg2 > 0 )
        {
            iTime = arg2;
            sFormat = DEFAULT_FORMAT_STR;
        }
        else
            return 0;
    }
    // 兩個參數都有時
    if( arg1 && arg2 )
    {
        if( intp(arg1) && arg1 > 0 && stringp(arg2) )
        {
            iTime = arg1;
            sFormat = arg2;
        }
        else if( stringp(arg1) && intp(arg2) && arg2 > 0 )
        {
            iTime = arg2;
            sFormat = arg1;
        }
        else
            return 0;
    }
    return ctime_format_real( iTime, sFormat );
}