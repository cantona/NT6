inherit ROOM;

void create()
{
  set("short", "雪山寺");
        set("long", @LONG
這裡是雪山寺的山門，門前是絡繹不絕的進香朝聖的信徒而有的
甚至來自烏絲藏西南的波絲。山門前站了個手持法器的葛倫布在維持
秩序，東方是一條青石板舖成的山路。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "north"    : __DIR__"frontyard",
                "eastdown" : "/d/xuedao/nroad4",
        ]));
        set("objects", ([
                CLASS_D("xueshan") + "/gelunbu": 1,
                "/d/wudang/npc/guest": 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object glb;

        if (dir != "north" ||
            ! objectp(glb = present("ge lunbu", this_object())))
                return ::valid_leave(me, dir);

        return glb->permit_pass(me, dir);
}