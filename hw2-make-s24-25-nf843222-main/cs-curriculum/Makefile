# I had problems with git add commit push -- I think its the token and I haven't resolved it yet ... Manually added code from VSCode

.PHONY: clean

high-school-diploma:
	@touch high-school-diploma

cs2400: high-school-diploma
	@touch cs2400

cs2401: cs2400
	@touch cs2401

cs3000: cs2401
	@touch cs3000

cs3610: cs2401 cs3000
	@touch cs3610

cs3200: cs2401
	@touch cs3200

cs3560:
	@touch cs3560

cs4000: cs3560 cs3610
	@touch cs4000

cs4040: cs3610
	@touch cs4040

cs4560: cs3560 cs3610
	@touch cs4560

cs4561: cs4560
	@touch cs4561

cs4100: cs3200
	@touch cs4100

# This target is placed here on purposed. This location
# is incorrect, you have to fix this. -- Fixed

undergraduate-degree: cs4040 cs4561 cs4000 cs4100
	@touch undergraduate-degree

undergraduateDegree: cs4040 cs4561 cs4000 cs4100
	@touch undergraduate-degree

clean:
	-$(RM) cs* high-school-diploma undergraduate-degree
