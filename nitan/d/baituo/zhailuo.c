inherit ROOM;

void create()
{
        set("short", "小宅落");
        set("long", @LONG
這裡是一個樹影婆娑的靜謐的小宅落，當中放著一口烏黑發亮的
大水缸。白駝山上常年積雪，這裡的主人架起一條長長的竹渠，把清
涼的雪水引到家中的水缸裡來。
LONG );
        set("exits", ([
                "west" : __DIR__"liangong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "baituo");
        set("resource/water", 1); 
        setup();
        replace_program(ROOM);
}