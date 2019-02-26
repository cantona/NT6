inherit ROOM;
void create()
{
        set("short", "七曲九迴廊");
        set("long",
"這裏是七、八十道長廊，相互接連，連綿不絕，直是無窮無盡。每個\n"
"長廊轉彎處都有一盞宛如鬼火般搖晃不定的黃燈。廊邊的潭水在燈光照射\n"
"下發出墨綠的異光。\n"
);
        set("no_magic", "1");

        setup();
}
int valid_leave(object me, string dir)
{
     if( random(query("kar", me))>26){
    message_vision("只聽地板吱呀呀幾聲想後，地板突然翻了起來，$N一下掉了進去。\n
",me);
     me->move("/d/llszhuang/hole");
     return notify_fail("");}
     return ::valid_leave(me, dir);
}
