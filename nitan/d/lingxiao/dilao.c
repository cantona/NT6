inherit ROOM;

void create()
{
        set("short", "地牢");
        set("long", @LONG
這間地牢在監獄的最下面，但卻有淡淡的陽光透入。地牢中
間，一個身影手持鐵鏈，傲然站在石柱旁。日光透將進來，只見
那人滿臉花白胡，身材魁梧，背脊微弓，倒似這間小小石室裝不
下他這個大身子似的，眼光耀如閃電，威猛無儔。 
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"didi",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/baizizai" : 1,
        ]));

        setup(); 
        replace_program(ROOM);
}
