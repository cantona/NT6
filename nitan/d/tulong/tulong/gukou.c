inherit ROOM;
void create()
{
        set("short","山谷口");
        set("long", @LONG
進得谷口，只見一片青草地上擺著七八張方桌，除了東首第一席外，每張桌
旁都已坐了人。各門各派的掌門、幫主都在裡面了。
LONG );
        set("no_fight",1);
        set("exits",([
                "west":"/d/tulong/tulong/daobian",
                "east":"/d/tulong/tulong/huichang",
        ]));

setup();
}
