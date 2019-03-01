// /d/changan/dayan.c

inherit  ROOM;

void  create  ()
{
        set  ("short",  "大雁塔");
        set  ("long",  @LONG
唐永徽三年，聖僧玄奘為保護佛家經書，由唐高宗資助建成此塔。
在《三藏法師傳》卷三中記載：摩揭國有一寺，一雁離群落羽，摔死地
上，僧以為雁即菩薩，建塔紀念，故名大雁塔。
LONG);
        set("exits",  ([  //sizeof()  ==  4
                "northwest"  :  __DIR__"road5",
        ]));
        set("outdoors",  "changan");
        set("coor/x", -10710);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}