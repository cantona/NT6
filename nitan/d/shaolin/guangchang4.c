// Room: /d/shaolin/guangchang4.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "精進場");
        set("long", @LONG
這是後殿前的精進場，廣場青磚鋪地，因為多年的踩踏而凹凸不
平。前後各是兩堵高牆，把整個廣場夾在中間，形成一個窄窄的長方
形。西邊開了扇小門，一股香氣裊裊地飄了過來。北面是個大門，幾
位僧人在此把守。
LONG );
        set("exits", ([
                "south" : __DIR__"guangchang3",
                "north" : __DIR__"houdian",
                "northup" : __DIR__"putiyuan",
        ]));
        set("outdoors", "shaolin");
        set("objects",([
                CLASS_D("shaolin") + "/hui-kong" : 1,
                __DIR__"npc/seng-bing3" : 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ((!myfam || myfam["family_name"] != "少林派") && dir == "northup" &&
                objectp(present("hui kong", environment(me))))
                        return notify_fail("慧空喝道：你不是少林出家弟子，不得進入後殿。\n");
        return ::valid_leave(me, dir);
}