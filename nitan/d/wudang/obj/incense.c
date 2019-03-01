// incense.c 香火
// Last Modified by winder on Aug. 18 2002

inherit ITEM;
void wear(int);

int worn;

void create()
{
        set_name("香火",({"incense"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一枝剛造出來的香火，還帶着松枝的香氣。\n");
                set("unit", "枝");
                set("value", 100);
                set("no_drop", 1);
                set("no_get", 1);
        }
        setup();
}

void init()
{
        worn = 0;
        call_out("wear", 120, 1); 
}
void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", "這是一枝貢奉用的香火，但已經開始失去香味了。\n");
                call_out("wear", 120, phase+1); 
                break;
        case 2:
                set("long", "這是一枝放了很久的香火，幾乎完全失去香氣了。\n");
                call_out("wear", 120, phase+1); 
                break;
        case 3:
                destruct(this_object());
                break;
        }        
}

// End of File 

