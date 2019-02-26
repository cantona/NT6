inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這裏是梅莊弟子練功勞累的時候，休息的地方，這裏經常可以聽
到如雷的鼾聲，這裏簡單的放着幾張墊子，幾牀棉被，幾個枕頭，而
且梅莊弟子雖然經常打掃這裏，但這裏仍然凌亂不堪，很多梅莊弟子
一進這裏，倒頭便睡，顯是過於疲勞的緣故。 
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