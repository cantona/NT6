// Room: /yangzhou/caotang.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "湖上草堂");
        set("long", @LONG
湖上草堂面西三楹。內懸嘉慶揚州知府伊秉綬書題額“湖上草堂”
及集句楹聯(lian)。堂外平台圍以石欄，柱頭雕有石獅，欄板為古松紋
飾，平台中植有一對百年紫薇，夏日紅花累累。欄外置畫舫碼頭。草堂
之北、玉佛洞前有唐代銀杏枯木兩片，一大一小，形似千年枯樹，上攀
古藤凌霄，枯木系木。銀杏木質堅韌，至今尚未腐朽，敲擊有聲。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIW"
        白        幽
        雲        賞
        初        未
        晴        已

        舊        高
        雨        潭
        適        轉
        至        清
\n"NOR
        ]));
        set("exits", ([
                "west"    : __DIR__"lunlian",
                "northup" : __DIR__"guanyindian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", 110);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}