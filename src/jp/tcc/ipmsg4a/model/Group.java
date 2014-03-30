package jp.tcc.ipmsg4a.model;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

public class Group implements Comparable<Group>, Iterable<User>{
	private String name;
	private Set<User> users = new HashSet<User>();
	
	public Group(String name, User... users){
		this.name = name;
		this.add(users);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public void add(User... users){
		this.users.addAll(Arrays.asList(users));
	}

	@Override
	public int compareTo(Group another) {
		return this.name.compareTo(another.name);
	}

	@Override
	public Iterator<User> iterator() {
		return this.users.iterator();
	}
	
	
	
}
