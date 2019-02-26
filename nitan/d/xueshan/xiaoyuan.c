inherit ROOM;

void create()
{
        set("short", "小院");
        set("long", @LONG
這裏是寺內的小院，收拾的相當乾淨利索。來來往往的香客和喇
 嘛，一邊在暗示着雪山寺香火之盛，一邊也好像在表示喇嘛的口福也
真不壞。因為北邊就是個廚房。
LONG );
        set("outdoors", "xueshan");
        set("exits", ([
                "west" : __DIR__"guangchang",
                "north" : __DIR__"chufang",
        ]));
        setup();
        replace_program(ROOM);
}