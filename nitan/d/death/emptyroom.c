inherit ROOM;

void create ()
{
        set ("short", "背陰山後");
        set ("long", @LONG

這裡是陰司背陰山下，周圍一片荒涼，不見草木，一片寂靜中
只有陰風呼呼地刮著。山腳下淡發紅光鬼燄，傳說中的陰司十
八層地獄就在那裡。從沒有人從那裡活著出去。


LONG);

        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_get", "eat");
        add_action("do_get", "get");
        add_action("do_get", "kill");
        add_action("do_get", "fight");
        add_action("do_get", "cast");
        add_action("do_get", "bian");
        add_action("do_get", "fly");
        add_action("do_get", "look");
        add_action("do_get", "l");
        add_action("do_get", "perform");
        add_action("do_get", "steal");
   
}
int do_get(string arg)
{
        return 1;
}
