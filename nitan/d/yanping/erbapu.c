// Room: /d/yanping/erbapu.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "廿八舖");
        set("long", @LONG
廿八舖高居仙霞嶺上，四望群山連綿，長風振崗，十分爽利。這裡
是個很小的小村落，雖然南來北往的客商繁多，可是也只有一家小小客
店，店門書著一聯：“到來福地非為福，出得仙霞始為仙”。極言閩道
之艱。
LONG );
        set("exits", ([
                "north"     : __DIR__"xianxialing",
                "southdown" : __DIR__"shandao1",
                "west"      : __DIR__"kedian",
        ]));
        set("objects", ([
                "/d/huashan/npc/haoke" : 2,
        ]));
        set("outdoors", "jiangnan");
        set("coor/x", 1500);
        set("coor/y", -4000);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}