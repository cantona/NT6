// Room: /guiyun/huayuan.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這是一處典型的江南園林，規模雖不大，構造得卻頗為精致，想必
當年建園之人很費了一番心力。園中花氣襲人，鶯啼燕舞，柳條隨風，
綠波盪漾，只待得片刻便令人如沐春風，流連忘返。
LONG );
        set("outdoors", "guiyun");
        set("exits", ([
                "east" : __DIR__"zoulang9",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoju" : 1,
        ]));
        set("coor/x", 250);
        set("coor/y", -800);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}