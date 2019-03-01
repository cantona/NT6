inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這裡是一條塵土飛揚的大官道，它是連接汝州的主幹道。官
道很是寬廣，足可容得下十馬並馳。
LONG);
        set("exits", ([
                "west"  : __DIR__"xiaozheng",
                "east"  : __DIR__"shang_road2",
        ]));
        set("outdoors", "ruzhou");
        setup();
        replace_program(ROOM);
}