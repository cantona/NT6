inherit ROOM;
string *names=({
        __DIR__"hole5",
        __DIR__"hole7",
        __DIR__"hole6",
        __DIR__"hole5",
} );
void create()
{
        set("short", "洞穴");
        set("long",
"山巖下祕洞，曲折深邃，有如諸葛武侯之八卦迷陣一般，幽謎繁複處\n"
"尤有過之。越是深入越是陰濕黝暗，到後來竟已難見五指。\n"
);
        set("no_magic", "1");
        setup();
}
void reset()
{
        int i,j;
        string temp;
        ::reset();
        for (i=0;i<=3;i++)
        {
                j=random(4);
                temp=names[j];
                names[j]=names[i];
                names[i]=names[j];
                names[i]=temp;
        }
        set("exits", ([
                "north" : names[0],
                "south" : names[1],
                "east" : names[2],
                "west" : names[3],
        ]));
}
