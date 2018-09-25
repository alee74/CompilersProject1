
### Building
To build ``reader`` simply enter ``make`` or ``make reader``
while in the root directory.

For additional information regarding invocation or usage,
simply enter `reader -h` or `reader --help`.

### Output
My output is formatted using tabs. Thus, the alignment of
ILOC code (-p) and default ouput varies with tab width,
register numbers, and constant values.
Token output (-t) remains unaffected, as it does not 
utilize tabs.

A few notes and useful tips:

  * Unix has a `tabs` command that allows you to set the
  tab width for a terminal. To set the tab width to 4 spaces,
  simply enter `tabs -4` at the prompt.
  
  * Default output is formatted most consistently when tab
  width is set to 8. Any other value causes the column
  headers (first two rows) to be misaligned. Columns widen
  when register numbers reach 100 or constant values exceed
  9,999.
  
  * ILOC code (-p) is consistent for tab widths greater
  than 8. That is to say, I did not encounter a test case that
  caused the assignment arrows to fall out of alignment for
  tab width of 9. `tabs -10` is optimal for appearance.
