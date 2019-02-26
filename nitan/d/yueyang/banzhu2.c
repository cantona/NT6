// Room: /d/yueyang/banzhu1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "斑竹林");
        set("long", @LONG
這裏是一片斑竹林。湖風吹來，一陣葉響。斑竹又叫湘妃竹，倘若
將斑竹移栽別處，第二年斑跡就會消失得無影無蹤，如果再將這株竹子
移回君山，下一年又是斑痕累累的了。唐代高駢曾寫有《湘浦曲》雲：
“虞帝南巡競不還，二妃幽怨水雲間。當時垂淚知多少？直到如今竹且
斑”。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"banzhu2",
                "west"      : __DIR__"erfeimu",
                "south"     : __DIR__"banzhu1",
                "north"     : __DIR__"banzhu3",
        ]));
        set("coor/x", -1660);
        set("coor/y", 2300);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}