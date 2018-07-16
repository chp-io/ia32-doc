options_categories = [
    'group',
    'definition',
    'struct',
    'struct_field',
    'bitfield',
    'bitfield_field',
]

options_comment_subfields = [
    'short_description',
    'long_description',
    'note',
    'access',
    'remarks',
    'see_also',
    'reference'
]

options_other_subfields = [
    'extra_empty_line',
    'no_indent',
    'prefer_alternative_names',
]

options_subfields = options_comment_subfields + options_other_subfields


class DocProcessorOptions(object):
    def __init__(self, **kwargs):
        for category in options_categories:
            #
            # Create subfields for each option category, e.g.: group_short_description,
            # struct_note, ...
            #
            for subfield in options_subfields:
                setattr(self, f'{category}_{subfield}', True)

            #
            # Create common property getter for *_comments (e.g.: definition_comments),
            # which will simply return if all comment subfields are True or False.
            #
            def comments_getter(self_, category_=category):
                return all(
                    getattr(self_, f'{category_}_{comment_subfield_}')
                    for comment_subfield_ in options_comment_subfields
                )

            #
            # Create common property setter for *_comments (e.g.: definition_comments),
            # which will simply set all comment subfields to desired value.
            #
            # Note that small hack is used with any() to run this expression as a comprehension.
            # Use of any is possible, because setattr() returns None.
            #
            def comments_setter(self_, value_, category_=category):
                any(
                    setattr(self_, f'{category_}_{comment_subfield_}', value_)
                    for comment_subfield_ in options_comment_subfields
                )

            setattr(DocProcessorOptions, f'{category}_comments', property(comments_getter, comments_setter))

        #
        # Create common property getter/setter for *_prefer_alternative_names.
        #
        def prefer_alternative_names_getter(self_):
            return all(
                getattr(self_, f'{category_}_prefer_alternative_names')
                for category_ in options_categories
            )

        def prefer_alternative_names_setter(self_, value_):
            any(
                setattr(self_, f'{category_}_prefer_alternative_names', value_)
                for category_ in options_categories
            )

        DocProcessorOptions.prefer_alternative_names = property(
            prefer_alternative_names_getter,
            prefer_alternative_names_setter
        )

        #
        # Additional options for individual categories.
        #
        # Group category.
        #
        self.group_defgroup = True

        #
        # Definition category.
        #
        self.definition_no_indent = True

        #
        # Bitfield category.
        #
        self.bitfield_field_with_define_bit = True
        self.bitfield_field_with_define_mask = True
        self.bitfield_field_with_define_get = True

        def bitfield_field_with_define_getter(self_):
            return all([
                self_.bitfield_field_with_define_bit,
                self_.bitfield_field_with_define_mask,
                self_.bitfield_field_with_define_get
            ])

        def bitfield_field_with_define_setter(self_, value_):
            self_.bitfield_field_with_define_bit = value_
            self_.bitfield_field_with_define_mask = value_
            self_.bitfield_field_with_define_get = value_

        DocProcessorOptions.bitfield_field_with_define = property(
            bitfield_field_with_define_getter,
            bitfield_field_with_define_setter
        )

        for option_name, option_value in kwargs.items():
            if not hasattr(self, option_name):
                raise Exception(f'{option_name} is not valid option!')

            setattr(self, option_name, option_value)


#
# TWO_WORDS -> twoWords
#
def to_camelcase_lower(text):
    return ''.join(e.title() for e in text.split('_'))


#
# TWO_WORDS -> TwoWords
#
def to_camelcase_upper(text):
    return ''.join(e.title() for e in text.split('_'))


#
# TWO_WORDS -> two_words
#
def to_snake_case_lower(text: str) -> str:
    return text.lower()


#
# TWO_WORDS -> TWO_WORDS
#
def to_snake_case_upper(text: str) -> str:
    return text.upper()


def main():
    o = DocProcessorOptions(definition_access=True)
    setattr(o, 'group_comments', False)
    i = 0


if __name__ == '__main__':
    main()

#######################################################################################################################


class DocProcessorContext(object):
    def __init__(self,
                 definition_comments: bool=True,
                 definition_new_line: bool=True,
                 definition_no_indent: bool=True,
                 bitfield_field_comments: bool=True,
                 bitfield_field_with_definitions: bool=True,
                 prefer_alternative_names: bool=True):
        self.definition_comments = definition_comments
        self.definition_new_line = definition_new_line
        self.definition_no_indent = definition_no_indent
        self.bitfield_field_comments = bitfield_field_comments
        self.bitfield_field_with_definitions = bitfield_field_with_definitions
        self.prefer_alternative_names = prefer_alternative_names


class DocProcessorContextStackPush(object):
    def __init__(self, ctx_stack: 'DocProcessorContextStack', new_ctx: DocProcessorContext):
        self.ctx_stack = ctx_stack
        self.new_ctx = new_ctx

    def __enter__(self):
        self.ctx_stack.ctx_stack.append(self.ctx_stack.ctx)
        self.ctx_stack.ctx = self.new_ctx

    def __exit__(self, type, value, traceback):
        self.ctx_stack.ctx = self.ctx_stack.ctx_stack.pop()


class DocProcessorContextStack(object):
    def __init__(self):
        self.ctx = DocProcessorContext()
        self.ctx_stack = []

    def push(self, new_ctx) -> DocProcessorContextStackPush:
        return DocProcessorContextStackPush(self, new_ctx)

    def __getattr__(self, item):
        return getattr(self.ctx, item)

