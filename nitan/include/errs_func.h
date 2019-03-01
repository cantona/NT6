// by naihe 200?.??.??   不記得什麼時候寫的了
// 有時候可以替代 notify_fail() ，在一些 add_action() 函數裡 return errs() 可以禁止繼續執行。
varargs int errs(string msg, object who)
{
        if( !msg )
                return 1;
        if( objectp(who) )
                tell_object( who, msg );
        else
                write( msg );
        return 1;
}

