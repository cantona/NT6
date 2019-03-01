inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
空空盪盪一個山洞，倒也還算幹凈，盡頭擺了一張石床。
LONG );
        set("exits", ([
                "out" : __DIR__"sroad8",
        ]));
        set("objects", ([
                __DIR__"obj/dachang" :1,
                CLASS_D("xuedao")+"/diyun" :1, 
                __DIR__"npc/shuisheng" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
