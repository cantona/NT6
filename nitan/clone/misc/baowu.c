// Last modified by winder 2003.9.2
// /clone/misc/baowu.c

#include <ansi.h>
inherit ITEM;
string* titles = ({
        HIW"夜明珠"NOR,
        HIG"岫巖玉"NOR,
        HIY"和田玉"NOR,
        HIG"巴林玉"NOR,
        HIR"昌化雞血石"NOR,
        HIC"青田石"NOR,
        HIY"田黃石"NOR,
        YEL"壽山石"NOR,
        HIW"橄欖石"NOR,
        BLK"黑曜石"NOR,
        HIW"白寶石"NOR,
        HIR"紅寶石"NOR,
        HIG"綠寶石"NOR,
        HIG"綠鬆石"NOR,
        HIG"孔雀石"NOR,
        HIC"青金石"NOR,
        YEL"金"HIG"綠寶石"NOR,
        HIG"綠晶"NOR,
        HIM"紫水晶"NOR,
        HIY"軟玉"NOR,
        HIY"琥珀"NOR,
        HIB"藍寶石"NOR,
        HIW"鑽石"NOR,
        HIG"碧玉"NOR,
        HIW"水晶"NOR,
        GRN"翡翠"NOR,
        HIM"瑪瑙"NOR,
        GRN"貓兒眼"NOR,
        HIR"珊瑚"NOR,
        HIG"手鐲"NOR,
        WHT"玉杯"NOR,
        WHT"玉蓮花"NOR,
        CYN"玉帶"NOR,
        CYN"玉發簪"NOR,
        CYN"玉戒指"NOR,
        HIC"玉佩"NOR,
        WHT"玉如意"NOR,
        CYN"玉手鐲"NOR,
        WHT"玉盞"NOR,
        WHT"珍珠"NOR,
        HIG"祖母綠"NOR,
        HIG"玉西瓜"NOR,
});

void create()
{
        int i = random(sizeof(titles));
        set_name(titles[i], ({"bao wu"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "你挖出來的寶物，不知道有什麼作用。\n");
                set("unit", "個");
                set("no_sell", 1);
                set("no_put",1);
//                set("value", 50);
                set("no_beg",1);
                set("no_steal",1);
        }
}