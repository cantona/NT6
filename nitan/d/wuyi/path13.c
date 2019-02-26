// Room: /d/wuyi/path13.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是兩峯夾縫中的一條小路。路面是丹崖石板鋪就的，兩邊都是高
聳的山峯。路邊有條數尺寬的小溝，溝裏終年流動着清澈的泉水，水中
時而閃現寸許長的游魚。小路時寬時窄。窄時不過數尺，舉手可撫山巖。
寬處也有數丈，路邊便都是層疊的茶林。巖壁上流淌的泉水，滋潤着一
片片葱綠的希望。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"tianchejia",
                "south" : __DIR__"yingzuiyan",
        ]));
        set("objects", ([
                "/d/huashan/npc/youke" : random(3),
        ]));
        set("coor/x", 1400);
        set("coor/y", -4910);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
