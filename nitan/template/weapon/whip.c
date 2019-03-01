// sword.c
// The template of auto-created sword.
// An example of object template.

// 包含模板系統宏定義文件
#include <template.h>

// 繼承模板物件
inherit TEMPLATE_OB;

// 將所需數據保存在變量中

// dbase 格式
mixed *dbase_format = ({ "long", "value" });

// 函數格式
mixed *function_format = ({ "set_weight", "init_damage" });

// 模板數據
mapping template_data = ([
        "liangyin whip" : ({ ({ "這是一柄銀光閃閃的亮銀鞭，上面發出陣陣寒氣襲人奪目。\n", 100 }), ({ 5000,  20, }), }),
        "zhujie whip"   : ({ ({ "這是一柄竹節鋼鞭。\n", 150 }), ({ 5000,  40, }), }),
        "baowei whip"   : ({ ({ "這是一柄豹尾鞭。\n", 200 }), ({ 5000, 60, }), }),
        "dajiang whip"  : ({ ({ "這是一柄打將鞭。\n", 250 }), ({ 5000, 80, }), }),
        "tuogu whip"    : ({ ({ "這是一柄駝骨陰風鞭。\n", 300 }), ({ 5000, 100, }), }),
        "jinlong whip"  : ({ ({ "這是一柄金龍鞭。\n", 350 }), ({ 5000, 120, }), }),
        "huwei whip"    : ({ ({ "這是一柄虎尾鋼鞭。\n", 400 }), ({ 5000, 140, }), }),
        "bingtie whip"  : ({ ({ "這是一柄鑌鐵鞭。\n", 450 }), ({ 5000, 160, }), }),
        "longtou whip"  : ({ ({ "這是一柄龍頭鳳尾鞭。\n", 500 }), ({ 5000, 180, }), }),                
        "huyan whip"    : ({ ({ "這是一柄虎眼鋼鞭。\n", 550 }), ({ 5000, 200, }), }),  
        "jinsi whip"    : ({ ({ "這是一柄金絲軟鞭。\n", 600 }), ({ 5000, 220, }), }),  
        "hulu whip"     : ({ ({ "這是一柄葫蘆鞭。\n", 650 }), ({ 5000, 240, }), }),  
        "guigu whip"    : ({ ({ "這是一柄龜骨鞭。\n", 700 }), ({ 5000, 260, }), }),  
        "yugu whip"     : ({ ({ "這是一柄魚尾鞭。\n", 750 }), ({ 5000, 280, }), }),  
        "shegu whip"    : ({ ({ "這是一柄蛇骨鞭。\n", 800 }), ({ 5000, 300, }), }),  
        "yinsi whip"    : ({ ({ "這是一柄銀絲軟鞭。\n", 850 }), ({ 5000, 320, }), }),  
        "zheyun whip"   : ({ ({ "這是一柄遮雲掃龍鞭。\n", 900 }), ({ 5000, 350, }), }),         
]);

// 初始化模板
void create()
{
        setup();
}

// 在這裡配置是否使用全格式模式或格式對應模式
void setup()
{
        // 即基準文件為 "/inherit/template/weapon/sword.c"。
        set_base_file("weapon/whip");

        // 設置 dbase 格式
        set_dbase_format(dbase_format);

        // 設置函數格式
        set_function_format(function_format);

        // 設置模板數據
        set_template_data(template_data);

        ::setup();
}
