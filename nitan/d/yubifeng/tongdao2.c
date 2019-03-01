// /yubifeng/tongdao2.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "通道");
        set("long", @LONG
洞穴癒來癒窄，須得弓身而行方能通過，洞中到處是千年不化的尖
冰，有些處所的冰條如刀劍般鋒銳突出。有時頭頂撞上了堅冰尖角，隱
隱生疼。
LONG );
        set("exits", ([
                "north" : __DIR__"shimen",
                "west"  : __DIR__"tongdao1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6110);
        set("coor/y", 5120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}