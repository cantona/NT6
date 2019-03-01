// /d/xiakedao/road3.c 俠客島 山路3

inherit ROOM;
void create()
{
        set("short", "山路");
        set("long", @LONG
這是通往山頂的小路，路旁雜草叢生，夾雜着一些不知名的野
花。四周靜悄悄地沒有人聲。你深深吸口氣，一陣山野的芬芳直入
心扉。
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "northdown" : __DIR__"road2",
                "southup" : __DIR__"road4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -22040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}