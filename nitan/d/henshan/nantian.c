#include <ansi.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", "南天門");
        set("long", @LONG
到了南天門，才能望到衡山第一的祝融峰。南天門是花崗巖做成
的石碑坊，中門鐫有「南天門」三字橫額，左右二門的門楣上，分別
刻有「行雲」和「施雨」二字。楹聯(lian)破陋，顯見歲月已久。
LONG );
        set("item_desc",([
                "lian" : (: look_duilian :),
        ]));
        set("exits", ([
                "eastup"    : __DIR__"liuyunping",
                "northeast" : __DIR__"shiziyan",
                "northwest" : __DIR__"shanlu14",
                "southeast" : __DIR__"denggaotai",
                "southwest" : __DIR__"shanlu13",
        ]));
 
        set("objects", ([
                __DIR__"npc/dizi1" :  4,
        ]));

        set("outdoors", "henshan");
	set("coor/x", -6940);
	set("coor/y", -5520);
	set("coor/z", 20);
	setup();
}

string look_duilian()
{
        return
        HIC "\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※      ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　門　" HIC "※※        ※※" NOR + WHT "  路  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　可　" HIC "※※        ※※" NOR + WHT "  承  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　通　" HIC "※※        ※※" NOR + WHT "  絕  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" NOR + WHT "　天　" HIC "※※        ※※" NOR + WHT "  頂  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　仰　" HIC "※※        ※※" HIW "  俯  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　觀　" HIC "※※        ※※" HIW "  瞰  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　碧　" HIC "※※        ※※" HIW "  翠  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　落　" HIC "※※        ※※" HIW "  微  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　星　" HIC "※※        ※※" HIW "  巒  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　辰　" HIC "※※        ※※" HIW "  嶼  " HIC "※※\n"
        "\t※※　 　 ※※        ※※      ※※\n"
        "\t※※" HIW "　近　" HIC "※※        ※※" HIW "  低  " HIC "※※\n"
        "\t※※    　※※        ※※      ※※\n"
        "\t※※※※※※※        ※※※※※※※\n"
        "\t※※※※※※※        ※※※※※※※\n\n" NOR;
}