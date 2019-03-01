//ROOM: /d/yanziwu/tingxiang.c

inherit ROOM;

void create()
{
        set("short", "聽香水榭");
        set("long", @LONG
綠柳杏花叢中有八九間茅房，四周竹籬掩映，錯落有致，這就是
慕容公子的婢女阿朱的住所了。
LONG );
        set("exits", ([
            "west"  : __DIR__"biheqiao",
            "south" : __DIR__"shuiyun",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}