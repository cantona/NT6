inherit ROOM;

void create()
{
          set ("short", "中州道");
          set ("long", @LONG
這是條連接南北的交通要道，來往行人不斷。道旁的樹木
下多有作小生意的商人。向南是中州城，北面通向揚州。
LONG);

          set("outdoors", "zhongzhou");
          set("exits", ([
                  "south" : __DIR__"to_zhongzhou3",
                  "north" : __DIR__"to_zhongzhou",
        ]));

        set("coor/x", -150);
        set("coor/y", 40);
        set("coor/z", 10);
        setup();
}