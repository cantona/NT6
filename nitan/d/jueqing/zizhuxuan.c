#include <ansi.h>

inherit ROOM;

string look_ge();

void create()
{
        set("short", "紫竹軒");
        set("long", @LONG
到得此處，陣陣泥土的清香撲面而來，放眼四周只見不遠
處有一露天亭閣(ting ge)掩映於翠竹之下。
LONG);

        set("item_desc",([
                "ting ge" : (: look_ge :),
                "ting"    : (: look_ge :),
                "ge"      : (: look_ge :),
        ]));

        set("exits", ([
               "south"  : __DIR__"huayuan",
               "east"   : __DIR__"zhulin4",
        ]));

        set("objects", ([
              CLASS_D("jueqing") + "/zhi" : 1,
        ]));

        set("no_clean_up", 0);

        setup();

}

string look_ge()
{
        return HIC "\n但見亭閣掩映於翠竹之下，之上立有一橫匾，上書："
               HIG "\n\n"
        "\t\t※※※※※※※        \n"
        "\t\t※※※※※※※        \n"
        "\t\t※※      ※※        \n"
        "\t\t※※" NOR + MAG "　紫 " HIG " ※※\n" HIG    
        "\t\t※※　 　 ※※        \n" HIG 
        "\t\t※※" NOR + MAG "　竹 " HIG " ※※\n" HIG    
        "\t\t※※　 　 ※※        \n" HIG
        "\t\t※※" NOR + MAG "　軒 " HIG " ※※\n" HIG
        "\t\t※※      ※※\n"     
        "\t\t※※※※※※※\n" HIG
        "\t\t※※※※※※※\n\n" NOR;

}