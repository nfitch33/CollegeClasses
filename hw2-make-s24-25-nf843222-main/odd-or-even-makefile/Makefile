# I had problems with git add commit push -- I think its the token and I haven't resolved it yet ... Manually added code from VSCode

.PHONY: ItIsSurelyOdd

#Gets the total count of files and sees if they are odd or even
ItIsSurelyOdd:
 @count=$$(find . -maxdepth 1 -type f | wc -l); \ 
 if [$$((count % 2)) -eq 0 ]; then \
	echo "even"; \
 else \
	echo "odd"; \
 fi
