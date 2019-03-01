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
        // 英文名(索引)  : ({ 描述(long), ({ 重量(set_weight) - 傷害(init_damage) }), 額外基準文件 })
        "scimitar"       : ({ ({ "這是一柄身作弧形的彎刀。\n", 100 }),        ({ 7000,  20, }), }),
        "sabre"          : ({ ({"這是一柄狹長略彎的馬刀。\n", 200 }),        ({ 9000,  25, }), }),
        "fachion"        : ({ ({"這是一把既寬且長的大刀。\n", 300 }),        ({ 12000, 30, }), }),
        "claymore"       : ({ ({ "這是一把兩邊都帶刃的鋒銳長刀。\n", 400 }),  ({ 12000, 40, }), }),
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
        set_base_file("weapon/blade");

        // 設置 dbase 格式
        set_dbase_format(dbase_format);

        // 設置函數格式
        set_function_format(function_format);

        // 設置模板數據
        set_template_data(template_data);

        ::setup();
}
