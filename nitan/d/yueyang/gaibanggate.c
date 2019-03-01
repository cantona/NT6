// Room: /d/yueyang/gaibanggate.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "大門");
        set("long", @LONG
你來到一棟大屋前，大門口進進出出的都是一身乞丐打扮，于是你
突然醒悟，這裡就是江湖中的丐兒幫吧。大門破破舊舊的，久經風雨的
橫樑發黑開裂，長上了綠苔，只有兩個銅門環磨蹭得金光閃閃。
LONG );
        set("outdoors", "yueyang");
        set("exits", ([
                "north" : __DIR__"gaibangyuan",
                "south" : __DIR__"xijie",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/xi" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 5,
        ]));
	set("coor/x", -6210);
	set("coor/y", -3000);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "丐幫") && dir == "north" &&
                objectp(present("xi zhanglao", environment(me))))
                return notify_fail("奚長老攔住你說：此處乃本幫禁地，請止步。\n");

        return ::valid_leave(me, dir);
}