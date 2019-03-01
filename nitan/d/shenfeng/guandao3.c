inherit ROOM;

void create()
{
        set("short", "破舊長城");
        set("long", @LONG
昔日雄偉的長城已面目全非，歲月和戰爭已幾乎把它夷為
平地。唯一僅存的一點廢墟，都被歷代英雄的鮮血染成暗紅色。
這裡雖然是一片蕭殺，卻有幾株小樹從碎石的縫隙中擠出，給
人以一線生機的感覺。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"guandao4",
                  "east" : __DIR__"guandao2",
        ]));

        setup();
        replace_program(ROOM);
}