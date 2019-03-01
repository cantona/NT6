//miaorenbuluo.c

inherit ROOM;

void create()
{
        set("short", "苗人部落");
        set("long", @LONG
你眼前突然一亮，原來是走進了一個苗人部落。苗人們圍坐在火
堆邊，面色虔誠，好象在作某種祭神儀式。幾個巫士揮舞著木鏜，口
中念念有詞。突然，他們好象發現了你。
LONG );
        set("outdoors", "mingjiao");
        set("exits",([
              "north" : __DIR__"westroad2",
        ]));
        set("objects",([
                __DIR__"npc/miaozuwushi":4,        
        ]));
        setup();
        replace_program(ROOM);
}