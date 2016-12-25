package jp.tkmt25.androidtest.util;

import java.util.concurrent.Executors;

import android.os.Handler;
import android.view.View;

public class ViewClickBinder{
	public static interface ViewHandler<T extends View>{
		public void handle(T t);
	}
	
	public static <T1 extends View, T2 extends View> void bind(final T1 bindView, T2 clickView, final ViewHandler<T1> viewHandler){
		final Handler handler = new Handler();
		clickView.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Executors.newCachedThreadPool().execute(new Runnable(){

					@Override
					public void run() {
						handler.post(new Runnable(){

							@Override
							public void run() {
								viewHandler.handle(bindView);
								
							}
							
						});
						
					}
					
				});
				
				
			}
		});
	}
}
