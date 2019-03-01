inherit ROOM;

void create()
{
        set("short", "臥龍崗上");
        set("long", @LONG
山頂上有一大片開闊地，藍藍的天上飄著幾朵白雲，腳下是綠油
油的草地，淺淺的剛好可以蓋過腳面，散發著一種誘人的芳香舒服的
人直想躺在上面打滾。前面有幾間簡陋的竹舍。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "south" : __DIR__"zhushe",
                "northdown" : __DIR__"shanlu3",
        ]));

        setup();
        replace_program(ROOM);
}