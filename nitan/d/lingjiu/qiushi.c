inherit ROOM;

void create()
{
        set("short", "囚室");
        set("long", @LONG
這裏是「靈鷲宮」關押犯人的地方，屋中光線昏暗，氣味難聞。
現在這裏靜悄悄的，似乎虛竹子當上門主後，這裏便比以前輕靜了許
多。
LONG );
        set("exits", ([
                "east" : __DIR__"men1",
        ]));
        set("objects",([
                "/d/lingjiu/npc/wulaoda" : 1,
        ]));

        setup();
        replace_program(ROOM);
}