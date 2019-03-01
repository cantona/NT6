inherit ROOM;

void create()
{
        set("short", "監獄小廳");
        set("long", @LONG
這裡就是凌霄城的監獄入口。凌霄城的監獄專門用來關押犯
了門規的弟子，一些城中的作姦犯科，雞鳴狗盜之徒也順便收押
在此。凌霄向來一派所成，所以門規森嚴，倒也少有犯事者，但
這裡是凌霄重地，防守自也嚴密。
LONG );
        set("exits", ([
                "west" : __DIR__"iceroad3",
                "down" : __DIR__"laolang",
        ]));
        set("objects", ([ 
                __DIR__"npc/yan" : 1,
                __DIR__"npc/dizi" : 3,
        ])); 
        setup(); 
}

int valid_leave(object me, string dir)
{
        object yan;

        if (dir != "down" ||
            ! objectp(yan = present("yan wanpeng", this_object())))
                return ::valid_leave(me, dir);

        return yan->permit_pass(me, dir);
}