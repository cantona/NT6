inherit ROOM;

void create()
{
        set("short","絕谷");
        set("long",@LONG
還好，你運氣好，從萬丈深淵上摔下來，居然摔到厚厚的
雪堆上，不但沒斷腿少胳膊，連皮都沒傷到一點。但是，到了
這絕谷之下，如何上去倒是一大難題。
LONG);
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);
        setup();
} 

void init()
{
    add_action("do_pan", "climb");
}

int do_pan()
{
        object me = this_player();
            me->move(__DIR__"shiya");
            return 1;
}
