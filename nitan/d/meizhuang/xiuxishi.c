inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這裡是梅莊弟子練功勞累的時候，休息的地方，這裡經常可以聽
到如雷的鼾聲，這裡簡單的放著幾張墊子，幾床棉被，幾個枕頭，而
且梅莊弟子雖然經常打掃這裡，但這裡仍然凌亂不堪，很多梅莊弟子
一進這裡，倒頭便睡，顯是過于疲勞的緣故。 
LONG );
        set("sleep_room", 1);
        set("exits", ([
            "west" : __DIR__"zoulang2",
        ]));
        set("no_fight", 1);
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}