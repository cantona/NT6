//ROOM neishi.c
inherit ROOM;
void create()
{
        set("short", "小舍內室");
        set("long", @LONG
這裏是小舍內室。收拾得精細異常。你一進去，就發現牀沿坐着
一個打扮妖豔的人。那人也詫異地抬頭，你發現他居然是個男人，手
裏執着一枚繡花針！
LONG );
        set("exits", ([
             "west" : __DIR__"xiaoshe",
        ]));
        set("objects", ([
             CLASS_D("riyue") + "/dongfang": 1,
        CLASS_D("riyue") + "/first" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
