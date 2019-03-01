// This program is a part of NT MudLIB

// When an object is destructed, this function is called with every
// item in that room.  We get the chance to save users from being destructed.
// 環境遭到毀滅時, 所有內在物件都會呼叫此函式
void destruct_env_of(object ob)
{
        if( interactive(ob) )
        {
                tell_object(ob, "你所在的空間消失了，你現在身處在空虛縹緲之中。\n");
                ob->move(VOID_OB);
        }
}
