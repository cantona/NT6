// Room: /d/wuyi/path11.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是兩峰夾縫中的一條小路。路面是丹崖石板舖就的，兩邊都是高
聳的山峰。路邊有條數尺寬的小溝，溝裡終年流動著清澈的泉水，水中
時而閃現寸許長的遊魚。小路時寬時窄。窄時不過數尺，舉手可撫山巖。
寬處也有數丈，路邊便都是層疊的茶林。巖壁上流淌的泉水，滋潤著一
片片蔥綠的希望。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"dahongpao",
                "northwest" : __DIR__"liuxiangjian",
                "northeast" : __DIR__"yonglechansi",
        ]));
        set("objects", ([
                "/d/huashan/npc/youke" : random(3),
        ]));
        set("coor/x", 1390);
        set("coor/y", -4940);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
